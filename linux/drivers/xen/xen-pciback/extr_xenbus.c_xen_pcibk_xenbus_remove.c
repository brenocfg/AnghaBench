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
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct xen_pcibk_device {int dummy; } ;

/* Variables and functions */
 struct xen_pcibk_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pdev (struct xen_pcibk_device*) ; 

__attribute__((used)) static int xen_pcibk_xenbus_remove(struct xenbus_device *dev)
{
	struct xen_pcibk_device *pdev = dev_get_drvdata(&dev->dev);

	if (pdev != NULL)
		free_pdev(pdev);

	return 0;
}