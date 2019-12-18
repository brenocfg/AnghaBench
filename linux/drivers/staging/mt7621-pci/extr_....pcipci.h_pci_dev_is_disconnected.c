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
struct pci_dev {scalar_t__ error_state; } ;

/* Variables and functions */
 scalar_t__ pci_channel_io_perm_failure ; 

__attribute__((used)) static inline bool pci_dev_is_disconnected(const struct pci_dev *dev)
{
	return dev->error_state == pci_channel_io_perm_failure;
}