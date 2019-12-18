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
struct qcom_apcs_ipc {struct platform_device* clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 struct qcom_apcs_ipc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int qcom_apcs_ipc_remove(struct platform_device *pdev)
{
	struct qcom_apcs_ipc *apcs = platform_get_drvdata(pdev);
	struct platform_device *clk = apcs->clk;

	platform_device_unregister(clk);

	return 0;
}