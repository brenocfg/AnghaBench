#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tc6393xb_platform_data {scalar_t__ resume_restore; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EBUSY ; 
 struct tc6393xb_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int tc6393xb_ohci_disable (struct platform_device*) ; 

__attribute__((used)) static int tc6393xb_ohci_suspend(struct platform_device *dev)
{
	struct tc6393xb_platform_data *tcpd = dev_get_platdata(dev->dev.parent);

	/* We can't properly store/restore OHCI state, so fail here */
	if (tcpd->resume_restore)
		return -EBUSY;

	return tc6393xb_ohci_disable(dev);
}