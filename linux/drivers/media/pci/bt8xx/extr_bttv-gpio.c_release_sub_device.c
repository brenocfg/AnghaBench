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
struct device {int dummy; } ;
struct bttv_sub_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct bttv_sub_device*) ; 
 struct bttv_sub_device* to_bttv_sub_dev (struct device*) ; 

__attribute__((used)) static void release_sub_device(struct device *dev)
{
	struct bttv_sub_device *sub = to_bttv_sub_dev(dev);
	kfree(sub);
}