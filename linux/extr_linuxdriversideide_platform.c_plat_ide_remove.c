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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ide_host {int dummy; } ;

/* Variables and functions */
 struct ide_host* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_host_remove (struct ide_host*) ; 

__attribute__((used)) static int plat_ide_remove(struct platform_device *pdev)
{
	struct ide_host *host = dev_get_drvdata(&pdev->dev);

	ide_host_remove(host);

	return 0;
}