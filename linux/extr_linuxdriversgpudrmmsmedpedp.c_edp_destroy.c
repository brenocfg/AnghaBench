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
struct platform_device {int dummy; } ;
struct msm_edp {int /*<<< orphan*/ * ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_edp_ctrl_destroy (int /*<<< orphan*/ *) ; 
 struct msm_edp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void edp_destroy(struct platform_device *pdev)
{
	struct msm_edp *edp = platform_get_drvdata(pdev);

	if (!edp)
		return;

	if (edp->ctrl) {
		msm_edp_ctrl_destroy(edp->ctrl);
		edp->ctrl = NULL;
	}

	platform_set_drvdata(pdev, NULL);
}