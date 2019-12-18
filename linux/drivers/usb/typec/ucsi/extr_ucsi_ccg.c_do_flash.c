#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int mode; } ;
struct ucsi_ccg {TYPE_1__ info; struct device* dev; } ;
struct fw_config_table {float identity; } ;
struct firmware {char* data; int size; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  fw_cfg_sig ;
typedef  int /*<<< orphan*/  fw_cfg ;
typedef  enum enum_flash_mode { ____Placeholder_enum_flash_mode } enum_flash_mode ;

/* Variables and functions */
 int CCG4_ROW_SIZE ; 
 int CCG_DEVINFO_FWMODE_MASK ; 
 int CCG_DEVINFO_FWMODE_SHIFT ; 
 int CYACD_LINE_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FLASH_FWCT1_WR_CMD ; 
 int /*<<< orphan*/  FLASH_FWCT2_WR_CMD ; 
 int /*<<< orphan*/  FLASH_FWCT_SIG_WR_CMD ; 
 int /*<<< orphan*/  FLASH_WR_CMD ; 
 int FW1 ; 
 int FW2 ; 
 int FW_CFG_TABLE_SIG_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PRIMARY ; 
 int ccg_cmd_enter_flashing (struct ucsi_ccg*) ; 
 int ccg_cmd_jump_boot_mode (struct ucsi_ccg*,int /*<<< orphan*/ ) ; 
 int ccg_cmd_port_control (struct ucsi_ccg*,int) ; 
 int ccg_cmd_reset (struct ucsi_ccg*) ; 
 int ccg_cmd_validate_fw (struct ucsi_ccg*,int) ; 
 int ccg_cmd_write_flash_row (struct ucsi_ccg*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char** ccg_fw_names ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 scalar_t__ hex2bin (int /*<<< orphan*/ *,char const*,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,struct device*) ; 
 char* strnchr (char const*,int,char) ; 

__attribute__((used)) static int do_flash(struct ucsi_ccg *uc, enum enum_flash_mode mode)
{
	struct device *dev = uc->dev;
	const struct firmware *fw = NULL;
	const char *p, *s;
	const char *eof;
	int err, row, len, line_sz, line_cnt = 0;
	unsigned long start_time = jiffies;
	struct fw_config_table  fw_cfg;
	u8 fw_cfg_sig[FW_CFG_TABLE_SIG_SIZE];
	u8 *wr_buf;

	err = request_firmware(&fw, ccg_fw_names[mode], dev);
	if (err) {
		dev_err(dev, "request %s failed err=%d\n",
			ccg_fw_names[mode], err);
		return err;
	}

	if (((uc->info.mode & CCG_DEVINFO_FWMODE_MASK) >>
			CCG_DEVINFO_FWMODE_SHIFT) == FW2) {
		err = ccg_cmd_port_control(uc, false);
		if (err < 0)
			goto release_fw;
		err = ccg_cmd_jump_boot_mode(uc, 0);
		if (err < 0)
			goto release_fw;
	}

	eof = fw->data + fw->size;

	/*
	 * check if signed fw
	 * last part of fw image is fw cfg table and signature
	 */
	if (fw->size < sizeof(fw_cfg) + sizeof(fw_cfg_sig))
		goto not_signed_fw;

	memcpy((uint8_t *)&fw_cfg, fw->data + fw->size -
	       sizeof(fw_cfg) - sizeof(fw_cfg_sig), sizeof(fw_cfg));

	if (fw_cfg.identity != ('F' | ('W' << 8) | ('C' << 16) | ('T' << 24))) {
		dev_info(dev, "not a signed image\n");
		goto not_signed_fw;
	}
	eof = fw->data + fw->size - sizeof(fw_cfg) - sizeof(fw_cfg_sig);

	memcpy((uint8_t *)&fw_cfg_sig,
	       fw->data + fw->size - sizeof(fw_cfg_sig), sizeof(fw_cfg_sig));

	/* flash fw config table and signature first */
	err = ccg_cmd_write_flash_row(uc, 0, (u8 *)&fw_cfg,
				      FLASH_FWCT1_WR_CMD);
	if (err)
		goto release_fw;

	err = ccg_cmd_write_flash_row(uc, 0, (u8 *)&fw_cfg + CCG4_ROW_SIZE,
				      FLASH_FWCT2_WR_CMD);
	if (err)
		goto release_fw;

	err = ccg_cmd_write_flash_row(uc, 0, &fw_cfg_sig,
				      FLASH_FWCT_SIG_WR_CMD);
	if (err)
		goto release_fw;

not_signed_fw:
	wr_buf = kzalloc(CCG4_ROW_SIZE + 4, GFP_KERNEL);
	if (!wr_buf) {
		err = -ENOMEM;
		goto release_fw;
	}

	err = ccg_cmd_enter_flashing(uc);
	if (err)
		goto release_mem;

	/*****************************************************************
	 * CCG firmware image (.cyacd) file line format
	 *
	 * :00rrrrllll[dd....]cc/r/n
	 *
	 * :00   header
	 * rrrr is row number to flash				(4 char)
	 * llll is data len to flash				(4 char)
	 * dd   is a data field represents one byte of data	(512 char)
	 * cc   is checksum					(2 char)
	 * \r\n newline
	 *
	 * Total length: 3 + 4 + 4 + 512 + 2 + 2 = 527
	 *
	 *****************************************************************/

	p = strnchr(fw->data, fw->size, ':');
	while (p < eof) {
		s = strnchr(p + 1, eof - p - 1, ':');

		if (!s)
			s = eof;

		line_sz = s - p;

		if (line_sz != CYACD_LINE_SIZE) {
			dev_err(dev, "Bad FW format line_sz=%d\n", line_sz);
			err =  -EINVAL;
			goto release_mem;
		}

		if (hex2bin(wr_buf, p + 3, CCG4_ROW_SIZE + 4)) {
			err =  -EINVAL;
			goto release_mem;
		}

		row = get_unaligned_be16(wr_buf);
		len = get_unaligned_be16(&wr_buf[2]);

		if (len != CCG4_ROW_SIZE) {
			err =  -EINVAL;
			goto release_mem;
		}

		err = ccg_cmd_write_flash_row(uc, row, wr_buf + 4,
					      FLASH_WR_CMD);
		if (err)
			goto release_mem;

		line_cnt++;
		p = s;
	}

	dev_info(dev, "total %d row flashed. time: %dms\n",
		 line_cnt, jiffies_to_msecs(jiffies - start_time));

	err = ccg_cmd_validate_fw(uc, (mode == PRIMARY) ? FW2 :  FW1);
	if (err)
		dev_err(dev, "%s validation failed err=%d\n",
			(mode == PRIMARY) ? "FW2" :  "FW1", err);
	else
		dev_info(dev, "%s validated\n",
			 (mode == PRIMARY) ? "FW2" :  "FW1");

	err = ccg_cmd_port_control(uc, false);
	if (err < 0)
		goto release_mem;

	err = ccg_cmd_reset(uc);
	if (err < 0)
		goto release_mem;

	err = ccg_cmd_port_control(uc, true);
	if (err < 0)
		goto release_mem;

release_mem:
	kfree(wr_buf);

release_fw:
	release_firmware(fw);
	return err;
}