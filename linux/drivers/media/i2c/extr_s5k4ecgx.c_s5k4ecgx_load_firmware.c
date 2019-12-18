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
typedef  int /*<<< orphan*/  const u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_subdev {TYPE_1__* v4l2_dev; } ;
struct i2c_client {int dummy; } ;
struct firmware {scalar_t__ size; int /*<<< orphan*/  const* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FW_CRC_SIZE ; 
 int FW_RECORD_SIZE ; 
 int /*<<< orphan*/  REG_CMDBUF0_ADDR ; 
 int /*<<< orphan*/  S5K4ECGX_FIRMWARE ; 
 scalar_t__ crc32_le (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/  const*) ; 
 void* get_unaligned_le32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s5k4ecgx_i2c_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s5k4ecgx_write (struct i2c_client*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,scalar_t__,...) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5k4ecgx_load_firmware(struct v4l2_subdev *sd)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	const struct firmware *fw;
	const u8 *ptr;
	int err, i, regs_num;
	u32 addr, crc, crc_file, addr_inc = 0;
	u16 val;

	err = request_firmware(&fw, S5K4ECGX_FIRMWARE, sd->v4l2_dev->dev);
	if (err) {
		v4l2_err(sd, "Failed to read firmware %s\n", S5K4ECGX_FIRMWARE);
		return err;
	}
	regs_num = get_unaligned_le32(fw->data);

	v4l2_dbg(3, debug, sd, "FW: %s size %zu register sets %d\n",
		 S5K4ECGX_FIRMWARE, fw->size, regs_num);

	regs_num++; /* Add header */
	if (fw->size != regs_num * FW_RECORD_SIZE + FW_CRC_SIZE) {
		err = -EINVAL;
		goto fw_out;
	}
	crc_file = get_unaligned_le32(fw->data + regs_num * FW_RECORD_SIZE);
	crc = crc32_le(~0, fw->data, regs_num * FW_RECORD_SIZE);
	if (crc != crc_file) {
		v4l2_err(sd, "FW: invalid crc (%#x:%#x)\n", crc, crc_file);
		err = -EINVAL;
		goto fw_out;
	}
	ptr = fw->data + FW_RECORD_SIZE;
	for (i = 1; i < regs_num; i++) {
		addr = get_unaligned_le32(ptr);
		ptr += sizeof(u32);
		val = get_unaligned_le16(ptr);
		ptr += sizeof(u16);
		if (addr - addr_inc != 2)
			err = s5k4ecgx_write(client, addr, val);
		else
			err = s5k4ecgx_i2c_write(client, REG_CMDBUF0_ADDR, val);
		if (err)
			break;
		addr_inc = addr;
	}
fw_out:
	release_firmware(fw);
	return err;
}