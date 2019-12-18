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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ath10k_pci_diag_read_mem (struct ath10k*,int /*<<< orphan*/ ,void*,size_t) ; 

int ath10k_pci_hif_diag_read(struct ath10k *ar, u32 address, void *buf,
			     size_t buf_len)
{
	return ath10k_pci_diag_read_mem(ar, address, buf, buf_len);
}