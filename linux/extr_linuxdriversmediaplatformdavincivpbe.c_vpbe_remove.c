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
struct vpbe_device {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vpbe_device*) ; 
 struct vpbe_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int vpbe_remove(struct platform_device *device)
{
	struct vpbe_device *vpbe_dev = platform_get_drvdata(device);

	kfree(vpbe_dev);

	return 0;
}