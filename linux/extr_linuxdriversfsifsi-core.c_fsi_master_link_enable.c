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
struct fsi_master {int (* link_enable ) (struct fsi_master*,int) ;} ;

/* Variables and functions */
 int stub1 (struct fsi_master*,int) ; 

__attribute__((used)) static int fsi_master_link_enable(struct fsi_master *master, int link)
{
	if (master->link_enable)
		return master->link_enable(master, link);

	return 0;
}