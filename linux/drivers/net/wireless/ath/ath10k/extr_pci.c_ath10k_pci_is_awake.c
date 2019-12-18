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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_pci {scalar_t__ mem; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCIE_LOCAL_BASE_ADDRESS ; 
 scalar_t__ RTC_STATE_ADDRESS ; 
 scalar_t__ RTC_STATE_V_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ RTC_STATE_V_ON ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 

__attribute__((used)) static bool ath10k_pci_is_awake(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	u32 val = ioread32(ar_pci->mem + PCIE_LOCAL_BASE_ADDRESS +
			   RTC_STATE_ADDRESS);

	return RTC_STATE_V_GET(val) == RTC_STATE_V_ON;
}