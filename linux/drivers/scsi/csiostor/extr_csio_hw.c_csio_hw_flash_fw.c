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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct pci_dev {int device; struct device dev; } ;
struct fw_info {int dummy; } ;
struct fw_hdr {int dummy; } ;
struct firmware {unsigned int size; int /*<<< orphan*/ * data; } ;
struct csio_hw {int /*<<< orphan*/  fw_state; int /*<<< orphan*/  chip_id; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 int CSIO_HW_CHIP_MASK ; 
 int ECANCELED ; 
 int EINVAL ; 
 int ENOMEM ; 
 char* FW_FNAME_T5 ; 
 char* FW_FNAME_T6 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,char const*,...) ; 
 int csio_hw_prep_fw (struct csio_hw*,struct fw_info*,int /*<<< orphan*/  const*,unsigned int,struct fw_hdr*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ csio_is_t5 (int) ; 
 struct fw_info* find_fw_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fw_hdr*) ; 
 struct fw_hdr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,char const*,struct device*) ; 

__attribute__((used)) static int
csio_hw_flash_fw(struct csio_hw *hw, int *reset)
{
	int ret = -ECANCELED;
	const struct firmware *fw;
	struct fw_info *fw_info;
	struct fw_hdr *card_fw;
	struct pci_dev *pci_dev = hw->pdev;
	struct device *dev = &pci_dev->dev ;
	const u8 *fw_data = NULL;
	unsigned int fw_size = 0;
	const char *fw_bin_file;

	/* This is the firmware whose headers the driver was compiled
	 * against
	 */
	fw_info = find_fw_info(CHELSIO_CHIP_VERSION(hw->chip_id));
	if (fw_info == NULL) {
		csio_err(hw,
			"unable to get firmware info for chip %d.\n",
			CHELSIO_CHIP_VERSION(hw->chip_id));
		return -EINVAL;
	}

	/* allocate memory to read the header of the firmware on the
	 * card
	 */
	card_fw = kmalloc(sizeof(*card_fw), GFP_KERNEL);
	if (!card_fw)
		return -ENOMEM;

	if (csio_is_t5(pci_dev->device & CSIO_HW_CHIP_MASK))
		fw_bin_file = FW_FNAME_T5;
	else
		fw_bin_file = FW_FNAME_T6;

	if (request_firmware(&fw, fw_bin_file, dev) < 0) {
		csio_err(hw, "could not find firmware image %s, err: %d\n",
			 fw_bin_file, ret);
	} else {
		fw_data = fw->data;
		fw_size = fw->size;
	}

	/* upgrade FW logic */
	ret = csio_hw_prep_fw(hw, fw_info, fw_data, fw_size, card_fw,
			 hw->fw_state, reset);

	/* Cleaning up */
	if (fw != NULL)
		release_firmware(fw);
	kfree(card_fw);
	return ret;
}