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
struct pci_dev {int dummy; } ;
struct TYPE_3__ {struct pci_dev* pci; } ;
struct TYPE_4__ {TYPE_1__ c; } ;

/* Variables and functions */
 unsigned int bttv_num ; 
 TYPE_2__** bttvs ; 

struct pci_dev* bttv_get_pcidev(unsigned int card)
{
	if (card >= bttv_num)
		return NULL;
	if (!bttvs[card])
		return NULL;

	return bttvs[card]->c.pci;
}