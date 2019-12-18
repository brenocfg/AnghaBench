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
typedef  int u32 ;
struct firmware {int size; scalar_t__ data; } ;
struct cx8802_dev {int /*<<< orphan*/  core; TYPE_1__* pci; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BLACKBIRD_FIRM_IMAGE_SIZE ; 
 int /*<<< orphan*/  CX2341X_FIRM_ENC_FILENAME ; 
 int EINVAL ; 
 int EIO ; 
 int IVTV_CMD_HW_BLOCKS_RST ; 
 int /*<<< orphan*/  IVTV_REG_APU ; 
 int /*<<< orphan*/  IVTV_REG_ENC_SDRAM_PRECHARGE ; 
 int /*<<< orphan*/  IVTV_REG_ENC_SDRAM_REFRESH ; 
 int /*<<< orphan*/  IVTV_REG_HW_BLOCKS ; 
 int /*<<< orphan*/  IVTV_REG_SPU ; 
 int /*<<< orphan*/  IVTV_REG_VPU ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (scalar_t__,unsigned char const*,int) ; 
 int /*<<< orphan*/  memory_read (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  memory_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int register_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int register_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int blackbird_load_firmware(struct cx8802_dev *dev)
{
	static const unsigned char magic[8] = {
		0xa7, 0x0d, 0x00, 0x00, 0x66, 0xbb, 0x55, 0xaa
	};
	const struct firmware *firmware;
	int i, retval = 0;
	u32 value = 0;
	u32 checksum = 0;
	__le32 *dataptr;

	retval  = register_write(dev->core, IVTV_REG_VPU, 0xFFFFFFED);
	retval |= register_write(dev->core, IVTV_REG_HW_BLOCKS,
				 IVTV_CMD_HW_BLOCKS_RST);
	retval |= register_write(dev->core, IVTV_REG_ENC_SDRAM_REFRESH,
				 0x80000640);
	retval |= register_write(dev->core, IVTV_REG_ENC_SDRAM_PRECHARGE,
				 0x1A);
	usleep_range(10000, 20000);
	retval |= register_write(dev->core, IVTV_REG_APU, 0);

	if (retval < 0)
		dprintk(0, "Error with register_write\n");

	retval = request_firmware(&firmware, CX2341X_FIRM_ENC_FILENAME,
				  &dev->pci->dev);

	if (retval != 0) {
		pr_err("Hotplug firmware request failed (%s).\n",
		       CX2341X_FIRM_ENC_FILENAME);
		pr_err("Please fix your hotplug setup, the board will not work without firmware loaded!\n");
		return -EIO;
	}

	if (firmware->size != BLACKBIRD_FIRM_IMAGE_SIZE) {
		pr_err("Firmware size mismatch (have %zd, expected %d)\n",
		       firmware->size, BLACKBIRD_FIRM_IMAGE_SIZE);
		release_firmware(firmware);
		return -EINVAL;
	}

	if (memcmp(firmware->data, magic, 8) != 0) {
		pr_err("Firmware magic mismatch, wrong file?\n");
		release_firmware(firmware);
		return -EINVAL;
	}

	/* transfer to the chip */
	dprintk(1, "Loading firmware ...\n");
	dataptr = (__le32 *)firmware->data;
	for (i = 0; i < (firmware->size >> 2); i++) {
		value = le32_to_cpu(*dataptr);
		checksum += ~value;
		memory_write(dev->core, i, value);
		dataptr++;
	}

	/* read back to verify with the checksum */
	for (i--; i >= 0; i--) {
		memory_read(dev->core, i, &value);
		checksum -= ~value;
	}
	release_firmware(firmware);
	if (checksum) {
		pr_err("Firmware load might have failed (checksum mismatch).\n");
		return -EIO;
	}
	dprintk(0, "Firmware upload successful.\n");

	retval |= register_write(dev->core, IVTV_REG_HW_BLOCKS,
				 IVTV_CMD_HW_BLOCKS_RST);
	retval |= register_read(dev->core, IVTV_REG_SPU, &value);
	retval |= register_write(dev->core, IVTV_REG_SPU, value & 0xFFFFFFFE);
	usleep_range(10000, 20000);

	retval |= register_read(dev->core, IVTV_REG_VPU, &value);
	retval |= register_write(dev->core, IVTV_REG_VPU, value & 0xFFFFFFE8);

	if (retval < 0)
		dprintk(0, "Error with register_write\n");
	return 0;
}