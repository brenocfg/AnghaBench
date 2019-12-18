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
typedef  scalar_t__ u32 ;
struct ath10k_pci_supp_chip {scalar_t__ dev_id; scalar_t__ rev_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ath10k_pci_supp_chip*) ; 
 scalar_t__ MS (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC_CHIP_ID_REV ; 
 struct ath10k_pci_supp_chip* ath10k_pci_supp_chips ; 

__attribute__((used)) static bool ath10k_pci_chip_is_supported(u32 dev_id, u32 chip_id)
{
	const struct ath10k_pci_supp_chip *supp_chip;
	int i;
	u32 rev_id = MS(chip_id, SOC_CHIP_ID_REV);

	for (i = 0; i < ARRAY_SIZE(ath10k_pci_supp_chips); i++) {
		supp_chip = &ath10k_pci_supp_chips[i];

		if (supp_chip->dev_id == dev_id &&
		    supp_chip->rev_id == rev_id)
			return true;
	}

	return false;
}