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
struct goku_udc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct goku_udc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct goku_udc*) ; 

__attribute__((used)) static void gadget_release(struct device *_dev)
{
	struct goku_udc	*dev = dev_get_drvdata(_dev);

	kfree(dev);
}