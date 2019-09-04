#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  const u8 ;
struct fsi_master_acf {scalar_t__ gpio_clk_vreg; scalar_t__ gpio_dat_vreg; size_t cf_mem_size; int /*<<< orphan*/  cf_mem; int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/  const* data; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 size_t FW_FILE_NAME ; 
 int HDR_FW_SIZE ; 
 int HDR_OFFSET ; 
 int HDR_SYS_SIG ; 
 scalar_t__ SYS_SIG_SHARED ; 
 scalar_t__ SYS_SIG_SPLIT ; 
 scalar_t__ be16_to_cpup (int /*<<< orphan*/ *) ; 
 size_t be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_copro_firmware(struct fsi_master_acf *master)
{
	const struct firmware *fw;
	uint16_t sig = 0, wanted_sig;
	const u8 *data;
	size_t size = 0;
	int rc;

	/* Get the binary */
	rc = request_firmware(&fw, FW_FILE_NAME, master->dev);
	if (rc) {
		dev_err(
			master->dev, "Error %d to load firwmare '%s' !\n",
			rc, FW_FILE_NAME);
		return rc;
	}

	/* Which image do we want ? (shared vs. split clock/data GPIOs) */
	if (master->gpio_clk_vreg == master->gpio_dat_vreg)
		wanted_sig = SYS_SIG_SHARED;
	else
		wanted_sig = SYS_SIG_SPLIT;
	dev_dbg(master->dev, "Looking for image sig %04x\n", wanted_sig);

	/* Try to find it */
	for (data = fw->data; data < (fw->data + fw->size);) {
		sig = be16_to_cpup((__be16 *)(data + HDR_OFFSET + HDR_SYS_SIG));
		size = be32_to_cpup((__be32 *)(data + HDR_OFFSET + HDR_FW_SIZE));
		if (sig == wanted_sig)
			break;
		data += size;
	}
	if (sig != wanted_sig) {
		dev_err(master->dev, "Failed to locate image sig %04x in FW blob\n",
			wanted_sig);
		rc = -ENODEV;
		goto release_fw;
	}
	if (size > master->cf_mem_size) {
		dev_err(master->dev, "FW size (%zd) bigger than memory reserve (%zd)\n",
			fw->size, master->cf_mem_size);
		rc = -ENOMEM;
	} else {
		memcpy_toio(master->cf_mem, data, size);
	}

release_fw:
	release_firmware(fw);
	return rc;
}