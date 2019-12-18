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
struct anybuss_client_driver {int (* probe ) (struct anybuss_client*) ;} ;
struct anybuss_client {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (struct anybuss_client*) ; 
 struct anybuss_client* to_anybuss_client (struct device*) ; 
 struct anybuss_client_driver* to_anybuss_client_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int anybus_bus_probe(struct device *dev)
{
	struct anybuss_client_driver *adrv =
		to_anybuss_client_driver(dev->driver);
	struct anybuss_client *adev =
		to_anybuss_client(dev);

	if (!adrv->probe)
		return -ENODEV;
	return adrv->probe(adev);
}