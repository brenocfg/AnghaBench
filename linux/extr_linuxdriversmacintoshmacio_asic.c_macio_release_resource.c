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
struct macio_devres {int res_mask; } ;
struct macio_dev {int dummy; } ;

/* Variables and functions */
 struct macio_devres* find_macio_dr (struct macio_dev*) ; 
 scalar_t__ macio_resource_len (struct macio_dev*,int) ; 
 int /*<<< orphan*/  macio_resource_start (struct macio_dev*,int) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,scalar_t__) ; 

void macio_release_resource(struct macio_dev *dev, int resource_no)
{
	struct macio_devres *dr = find_macio_dr(dev);

	if (macio_resource_len(dev, resource_no) == 0)
		return;
	release_mem_region(macio_resource_start(dev, resource_no),
			   macio_resource_len(dev, resource_no));
	if (dr && resource_no < 32)
		dr->res_mask &= ~(1 << resource_no);
}