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
struct dmi_system_id {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static int tqmx86_create_platform_device(const struct dmi_system_id *id)
{
	struct platform_device *pdev;
	int err;

	pdev = platform_device_alloc("tqmx86", -1);
	if (!pdev)
		return -ENOMEM;

	err = platform_device_add(pdev);
	if (err)
		platform_device_put(pdev);

	return err;
}