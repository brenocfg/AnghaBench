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
struct qcom_socinfo {int /*<<< orphan*/  soc_dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct qcom_socinfo* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  soc_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socinfo_debugfs_exit (struct qcom_socinfo*) ; 

__attribute__((used)) static int qcom_socinfo_remove(struct platform_device *pdev)
{
	struct qcom_socinfo *qs = platform_get_drvdata(pdev);

	soc_device_unregister(qs->soc_dev);

	socinfo_debugfs_exit(qs);

	return 0;
}