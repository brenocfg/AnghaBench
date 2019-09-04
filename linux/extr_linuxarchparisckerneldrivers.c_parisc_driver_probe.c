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
struct parisc_driver {int (* probe ) (struct parisc_device*) ;} ;
struct parisc_device {struct parisc_driver* driver; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int stub1 (struct parisc_device*) ; 
 struct parisc_device* to_parisc_device (struct device*) ; 
 struct parisc_driver* to_parisc_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parisc_driver_probe(struct device *dev)
{
	int rc;
	struct parisc_device *pa_dev = to_parisc_device(dev);
	struct parisc_driver *pa_drv = to_parisc_driver(dev->driver);

	rc = pa_drv->probe(pa_dev);

	if (!rc)
		pa_dev->driver = pa_drv;

	return rc;
}