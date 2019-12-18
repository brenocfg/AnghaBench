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
struct qcom_glink {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct qcom_glink* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  qcom_glink_native_remove (struct qcom_glink*) ; 

__attribute__((used)) static int glink_rpm_remove(struct platform_device *pdev)
{
	struct qcom_glink *glink = platform_get_drvdata(pdev);

	qcom_glink_native_remove(glink);

	return 0;
}