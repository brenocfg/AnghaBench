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
struct device {int dummy; } ;
struct camif_dev {int /*<<< orphan*/ * clock; } ;

/* Variables and functions */
 size_t CLK_CAM ; 
 size_t CLK_GATE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct camif_dev* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int s3c_camif_runtime_suspend(struct device *dev)
{
	struct camif_dev *camif = dev_get_drvdata(dev);

	/* null op on s3c244x */
	clk_disable(camif->clock[CLK_CAM]);

	clk_disable(camif->clock[CLK_GATE]);
	return 0;
}