#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct TYPE_3__ {int /*<<< orphan*/  param; int /*<<< orphan*/  app; int /*<<< orphan*/  core; int /*<<< orphan*/  boot; } ;
struct mip4_ts {TYPE_2__* client; TYPE_1__ fw_version; } ;
struct mip4_fw_version {int boot; int core; int app; int param; } ;
struct mip4_bin_tail {int /*<<< orphan*/  ver_boot; int /*<<< orphan*/  bin_length; int /*<<< orphan*/  bin_start_addr; int /*<<< orphan*/  tail_mark; int /*<<< orphan*/  tail_size; } ;
struct firmware {size_t size; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MIP4_BIN_TAIL_MARK ; 
 size_t MIP4_BIN_TAIL_SIZE ; 
 int MIP4_BL_PAGE_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 size_t get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mip4_parse_fw_version (int /*<<< orphan*/  const*,struct mip4_fw_version*) ; 

__attribute__((used)) static int mip4_parse_firmware(struct mip4_ts *ts, const struct firmware *fw,
			       u32 *fw_offset_start, u32 *fw_size,
			       const struct mip4_bin_tail **pfw_info)
{
	const struct mip4_bin_tail *fw_info;
	struct mip4_fw_version fw_version;
	u16 tail_size;

	if (fw->size < MIP4_BIN_TAIL_SIZE) {
		dev_err(&ts->client->dev,
			"Invalid firmware, size mismatch (tail %zd vs %zd)\n",
			MIP4_BIN_TAIL_SIZE, fw->size);
		return -EINVAL;
	}

	fw_info = (const void *)&fw->data[fw->size - MIP4_BIN_TAIL_SIZE];

#if MIP4_FW_UPDATE_DEBUG
	print_hex_dump(KERN_ERR, MIP4_DEVICE_NAME " Bin Info: ",
		       DUMP_PREFIX_OFFSET, 16, 1, *fw_info, tail_size, false);
#endif

	tail_size = get_unaligned_le16(&fw_info->tail_size);
	if (tail_size != MIP4_BIN_TAIL_SIZE) {
		dev_err(&ts->client->dev,
			"wrong tail size: %d (expected %zd)\n",
			tail_size, MIP4_BIN_TAIL_SIZE);
		return -EINVAL;
	}

	/* Check bin format */
	if (memcmp(fw_info->tail_mark, MIP4_BIN_TAIL_MARK,
		   sizeof(fw_info->tail_mark))) {
		dev_err(&ts->client->dev,
			"unable to locate tail marker (%*ph vs %*ph)\n",
			(int)sizeof(fw_info->tail_mark), fw_info->tail_mark,
			(int)sizeof(fw_info->tail_mark), MIP4_BIN_TAIL_MARK);
		return -EINVAL;
	}

	*fw_offset_start = get_unaligned_le32(&fw_info->bin_start_addr);
	*fw_size = get_unaligned_le32(&fw_info->bin_length);

	dev_dbg(&ts->client->dev,
		"F/W Data offset: %#08x, size: %d\n",
		*fw_offset_start, *fw_size);

	if (*fw_size % MIP4_BL_PAGE_SIZE) {
		dev_err(&ts->client->dev,
			"encoded fw length %d is not multiple of pages (%d)\n",
			*fw_size, MIP4_BL_PAGE_SIZE);
		return -EINVAL;
	}

	if (fw->size != *fw_offset_start + *fw_size) {
		dev_err(&ts->client->dev,
			"Wrong firmware size, expected %d bytes, got %zd\n",
			*fw_offset_start + *fw_size, fw->size);
		return -EINVAL;
	}

	mip4_parse_fw_version((const u8 *)&fw_info->ver_boot, &fw_version);

	dev_dbg(&ts->client->dev,
		"F/W file version %04X %04X %04X %04X\n",
		fw_version.boot, fw_version.core,
		fw_version.app, fw_version.param);

	dev_dbg(&ts->client->dev, "F/W chip version: %04X %04X %04X %04X\n",
		 ts->fw_version.boot, ts->fw_version.core,
		 ts->fw_version.app, ts->fw_version.param);

	/* Check F/W type */
	if (fw_version.boot != 0xEEEE && fw_version.boot != 0xFFFF &&
	    fw_version.core == 0xEEEE &&
	    fw_version.app == 0xEEEE &&
	    fw_version.param == 0xEEEE) {
		dev_dbg(&ts->client->dev, "F/W type: Bootloader\n");
	} else if (fw_version.boot == 0xEEEE &&
		   fw_version.core != 0xEEEE && fw_version.core != 0xFFFF &&
		   fw_version.app != 0xEEEE && fw_version.app != 0xFFFF &&
		   fw_version.param != 0xEEEE && fw_version.param != 0xFFFF) {
		dev_dbg(&ts->client->dev, "F/W type: Main\n");
	} else {
		dev_err(&ts->client->dev, "Wrong firmware type\n");
		return -EINVAL;
	}

	return 0;
}