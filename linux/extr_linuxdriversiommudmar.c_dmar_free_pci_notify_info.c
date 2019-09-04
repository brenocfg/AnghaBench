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
struct dmar_pci_notify_info {int dummy; } ;

/* Variables and functions */
 void* dmar_pci_notify_info_buf ; 
 int /*<<< orphan*/  kfree (struct dmar_pci_notify_info*) ; 

__attribute__((used)) static inline void dmar_free_pci_notify_info(struct dmar_pci_notify_info *info)
{
	if ((void *)info != dmar_pci_notify_info_buf)
		kfree(info);
}