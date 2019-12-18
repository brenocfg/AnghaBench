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
struct pci_dev {int dummy; } ;
struct kgd_dev {int dummy; } ;
struct kfd_dev {int dummy; } ;
struct kfd2kgd_calls {int dummy; } ;

/* Variables and functions */

struct kfd_dev *kgd2kfd_probe(struct kgd_dev *kgd, struct pci_dev *pdev,
			      const struct kfd2kgd_calls *f2g)
{
	return NULL;
}