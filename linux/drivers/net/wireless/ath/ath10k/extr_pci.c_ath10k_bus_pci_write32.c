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
typedef  int /*<<< orphan*/  value ;
typedef  scalar_t__ u32 ;
struct ath10k_pci {scalar_t__ mem_len; scalar_t__ mem; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_sleep (struct ath10k*) ; 
 int ath10k_pci_wake (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ath10k_bus_pci_write32(struct ath10k *ar, u32 offset, u32 value)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	int ret;

	if (unlikely(offset + sizeof(value) > ar_pci->mem_len)) {
		ath10k_warn(ar, "refusing to write mmio out of bounds at 0x%08x - 0x%08zx (max 0x%08zx)\n",
			    offset, offset + sizeof(value), ar_pci->mem_len);
		return;
	}

	ret = ath10k_pci_wake(ar);
	if (ret) {
		ath10k_warn(ar, "failed to wake target for write32 of 0x%08x at 0x%08x: %d\n",
			    value, offset, ret);
		return;
	}

	iowrite32(value, ar_pci->mem + offset);
	ath10k_pci_sleep(ar);
}