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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRVNAME ; 
 int ENOMEM ; 
 struct platform_device* ERR_PTR (int) ; 
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int topology_logical_die_id (unsigned int) ; 
 struct platform_device** zone_devices ; 

__attribute__((used)) static struct platform_device *coretemp_device_add(unsigned int cpu)
{
	int err, zoneid = topology_logical_die_id(cpu);
	struct platform_device *pdev;

	if (zoneid < 0)
		return ERR_PTR(-ENOMEM);

	pdev = platform_device_alloc(DRVNAME, zoneid);
	if (!pdev)
		return ERR_PTR(-ENOMEM);

	err = platform_device_add(pdev);
	if (err) {
		platform_device_put(pdev);
		return ERR_PTR(err);
	}

	zone_devices[zoneid] = pdev;
	return pdev;
}