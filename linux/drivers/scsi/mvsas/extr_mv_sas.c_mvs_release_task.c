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
struct mvs_info {int dummy; } ;
struct domain_device {int dummy; } ;

/* Variables and functions */
 int WIDE_PORT_MAX_PHY ; 
 int /*<<< orphan*/  mvs_do_release_task (struct mvs_info*,int,struct domain_device*) ; 
 int mvs_find_dev_phyno (struct domain_device*,int*) ; 

void mvs_release_task(struct mvs_info *mvi,
		      struct domain_device *dev)
{
	int i, phyno[WIDE_PORT_MAX_PHY], num;
	num = mvs_find_dev_phyno(dev, phyno);
	for (i = 0; i < num; i++)
		mvs_do_release_task(mvi, phyno[i], dev);
}