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
struct sgi_w1_device {int /*<<< orphan*/  bus_master; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct sgi_w1_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  w1_remove_master_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sgi_w1_remove(struct platform_device *pdev)
{
	struct sgi_w1_device *sdev = platform_get_drvdata(pdev);

	w1_remove_master_device(&sdev->bus_master);

	return 0;
}