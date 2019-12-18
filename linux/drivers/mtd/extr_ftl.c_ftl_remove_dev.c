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
struct mtd_blktrans_dev {int dummy; } ;
typedef  int /*<<< orphan*/  partition_t ;

/* Variables and functions */
 int /*<<< orphan*/  del_mtd_blktrans_dev (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  ftl_freepart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ftl_remove_dev(struct mtd_blktrans_dev *dev)
{
	del_mtd_blktrans_dev(dev);
	ftl_freepart((partition_t *)dev);
}