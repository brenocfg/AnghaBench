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
struct s3c2410_wdt {int /*<<< orphan*/  wdt_device; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct s3c2410_wdt* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  s3c2410wdt_mask_and_disable_reset (struct s3c2410_wdt*,int) ; 
 int /*<<< orphan*/  s3c2410wdt_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s3c2410wdt_shutdown(struct platform_device *dev)
{
	struct s3c2410_wdt *wdt = platform_get_drvdata(dev);

	s3c2410wdt_mask_and_disable_reset(wdt, true);

	s3c2410wdt_stop(&wdt->wdt_device);
}