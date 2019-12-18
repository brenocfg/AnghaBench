#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int start; } ;
struct parisc_device {TYPE_1__ hpa; } ;
struct ibase_data_struct {int ioc_num; TYPE_2__* ioc; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  imask; int /*<<< orphan*/  ibase; } ;

/* Variables and functions */
 struct parisc_device* to_parisc_device (struct device*) ; 

__attribute__((used)) static int setup_ibase_imask_callback(struct device *dev, void *data)
{
	/* lba_set_iregs() is in drivers/parisc/lba_pci.c */
        extern void lba_set_iregs(struct parisc_device *, u32, u32);
	struct parisc_device *lba = to_parisc_device(dev);
	struct ibase_data_struct *ibd = data;
	int rope_num = (lba->hpa.start >> 13) & 0xf;
	if (rope_num >> 3 == ibd->ioc_num)
		lba_set_iregs(lba, ibd->ioc->ibase, ibd->ioc->imask);
	return 0;
}