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
struct amd5536udc {int dummy; } ;

/* Variables and functions */
 struct amd5536udc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct amd5536udc*) ; 

void gadget_release(struct device *pdev)
{
	struct amd5536udc *dev = dev_get_drvdata(pdev);
	kfree(dev);
}