#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icc_smd_rpm ; 

__attribute__((used)) static int qcom_icc_rpm_smd_probe(struct platform_device *pdev)
{
	icc_smd_rpm = dev_get_drvdata(pdev->dev.parent);

	if (!icc_smd_rpm) {
		dev_err(&pdev->dev, "unable to retrieve handle to RPM\n");
		return -ENODEV;
	}

	return 0;
}