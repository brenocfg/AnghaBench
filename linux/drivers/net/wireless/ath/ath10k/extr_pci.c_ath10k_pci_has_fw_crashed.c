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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_INDICATOR_ADDRESS ; 
 int FW_IND_EVENT_PENDING ; 
 int ath10k_pci_read32 (struct ath10k*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath10k_pci_has_fw_crashed(struct ath10k *ar)
{
	return ath10k_pci_read32(ar, FW_INDICATOR_ADDRESS) &
	       FW_IND_EVENT_PENDING;
}