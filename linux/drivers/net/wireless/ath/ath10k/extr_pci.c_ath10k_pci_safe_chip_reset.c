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
struct ath10k_pci {int (* pci_soft_reset ) (struct ath10k*) ;} ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int stub1 (struct ath10k*) ; 

__attribute__((used)) static int ath10k_pci_safe_chip_reset(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	if (!ar_pci->pci_soft_reset)
		return -ENOTSUPP;

	return ar_pci->pci_soft_reset(ar);
}