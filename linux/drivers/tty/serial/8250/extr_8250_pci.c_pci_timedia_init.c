#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {unsigned short const subsystem_device; } ;
struct TYPE_3__ {unsigned short* ids; int num; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* timedia_data ; 

__attribute__((used)) static int pci_timedia_init(struct pci_dev *dev)
{
	const unsigned short *ids;
	int i, j;

	for (i = 0; i < ARRAY_SIZE(timedia_data); i++) {
		ids = timedia_data[i].ids;
		for (j = 0; ids[j]; j++)
			if (dev->subsystem_device == ids[j])
				return timedia_data[i].num;
	}
	return 0;
}