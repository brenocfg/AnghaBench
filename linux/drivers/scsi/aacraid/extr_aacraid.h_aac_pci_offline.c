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
struct aac_dev {scalar_t__ handle_pci_error; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int aac_pci_offline(struct aac_dev *dev)
{
	return pci_channel_offline(dev->pdev) || dev->handle_pci_error;
}