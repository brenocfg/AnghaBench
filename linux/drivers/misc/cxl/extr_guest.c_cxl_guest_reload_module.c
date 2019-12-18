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
struct platform_device {int dummy; } ;
struct cxl {TYPE_1__* guest; } ;
struct TYPE_2__ {struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_guest_remove_adapter (struct cxl*) ; 
 int /*<<< orphan*/  cxl_of_probe (struct platform_device*) ; 

void cxl_guest_reload_module(struct cxl *adapter)
{
	struct platform_device *pdev;

	pdev = adapter->guest->pdev;
	cxl_guest_remove_adapter(adapter);

	cxl_of_probe(pdev);
}