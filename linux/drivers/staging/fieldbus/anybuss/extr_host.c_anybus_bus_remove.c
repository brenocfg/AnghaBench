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
struct device {int /*<<< orphan*/  driver; } ;
struct anybuss_client_driver {int (* remove ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_anybuss_client (struct device*) ; 
 struct anybuss_client_driver* to_anybuss_client_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int anybus_bus_remove(struct device *dev)
{
	struct anybuss_client_driver *adrv =
		to_anybuss_client_driver(dev->driver);

	if (adrv->remove)
		return adrv->remove(to_anybuss_client(dev));
	return 0;
}