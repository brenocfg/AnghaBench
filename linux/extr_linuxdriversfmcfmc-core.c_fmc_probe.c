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
struct fmc_driver {int (* probe ) (struct fmc_device*) ;} ;
struct fmc_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int stub1 (struct fmc_device*) ; 
 struct fmc_device* to_fmc_device (struct device*) ; 
 struct fmc_driver* to_fmc_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fmc_probe(struct device *dev)
{
	struct fmc_driver *fdrv = to_fmc_driver(dev->driver);
	struct fmc_device *fdev = to_fmc_device(dev);

	return fdrv->probe(fdev);
}