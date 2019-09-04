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
struct hd_struct {int dummy; } ;
struct device {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_free_devt (int /*<<< orphan*/ ) ; 
 struct hd_struct* dev_to_part (struct device*) ; 
 int /*<<< orphan*/  hd_free_part (struct hd_struct*) ; 
 int /*<<< orphan*/  kfree (struct hd_struct*) ; 

__attribute__((used)) static void part_release(struct device *dev)
{
	struct hd_struct *p = dev_to_part(dev);
	blk_free_devt(dev->devt);
	hd_free_part(p);
	kfree(p);
}