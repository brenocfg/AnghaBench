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
struct vop_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct vop_device* dev_to_vop (struct device*) ; 
 int /*<<< orphan*/  kfree (struct vop_device*) ; 

__attribute__((used)) static void vop_release_dev(struct device *d)
{
	struct vop_device *dev = dev_to_vop(d);

	kfree(dev);
}