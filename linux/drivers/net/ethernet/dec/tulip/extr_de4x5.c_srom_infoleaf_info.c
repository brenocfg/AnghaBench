#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
struct net_device {int /*<<< orphan*/  name; } ;
struct de4x5_private {scalar_t__ chipset; int useSROM; scalar_t__ device; int /*<<< orphan*/  infoleaf_offset; int /*<<< orphan*/  srom; int /*<<< orphan*/  infoleaf_fn; } ;
struct TYPE_2__ {scalar_t__ chipset; int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 int ENXIO ; 
 int INFOLEAF_SIZE ; 
 int /*<<< orphan*/  get_unaligned_le16 (scalar_t__*) ; 
 TYPE_1__* infoleaf_array ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
srom_infoleaf_info(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    int i, count;
    u_char *p;

    /* Find the infoleaf decoder function that matches this chipset */
    for (i=0; i<INFOLEAF_SIZE; i++) {
	if (lp->chipset == infoleaf_array[i].chipset) break;
    }
    if (i == INFOLEAF_SIZE) {
	lp->useSROM = false;
	printk("%s: Cannot find correct chipset for SROM decoding!\n",
	                                                          dev->name);
	return -ENXIO;
    }

    lp->infoleaf_fn = infoleaf_array[i].fn;

    /* Find the information offset that this function should use */
    count = *((u_char *)&lp->srom + 19);
    p  = (u_char *)&lp->srom + 26;

    if (count > 1) {
	for (i=count; i; --i, p+=3) {
	    if (lp->device == *p) break;
	}
	if (i == 0) {
	    lp->useSROM = false;
	    printk("%s: Cannot find correct PCI device [%d] for SROM decoding!\n",
	                                               dev->name, lp->device);
	    return -ENXIO;
	}
    }

	lp->infoleaf_offset = get_unaligned_le16(p + 1);

    return 0;
}