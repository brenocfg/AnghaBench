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

/* Variables and functions */
 int /*<<< orphan*/  DRVNAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  amb_pdev ; 
 int platform_device_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i5k_amb_add(void)
{
	int res = -ENODEV;

	/* only ever going to be one of these */
	amb_pdev = platform_device_alloc(DRVNAME, 0);
	if (!amb_pdev)
		return -ENOMEM;

	res = platform_device_add(amb_pdev);
	if (res)
		goto err;
	return 0;

err:
	platform_device_put(amb_pdev);
	return res;
}