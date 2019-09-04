#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_6__ {int /*<<< orphan*/  dev_id; } ;
typedef  TYPE_1__ dbdev_tab_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSCR_DEV2CUSTOM_ID (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* find_dbdev_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

u32 au1xxx_ddma_add_device(dbdev_tab_t *dev)
{
	u32 ret = 0;
	dbdev_tab_t *p;
	static u16 new_id = 0x1000;

	p = find_dbdev_id(~0);
	if (NULL != p) {
		memcpy(p, dev, sizeof(dbdev_tab_t));
		p->dev_id = DSCR_DEV2CUSTOM_ID(new_id, dev->dev_id);
		ret = p->dev_id;
		new_id++;
#if 0
		printk(KERN_DEBUG "add_device: id:%x flags:%x padd:%x\n",
				  p->dev_id, p->dev_flags, p->dev_physaddr);
#endif
	}

	return ret;
}