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
struct v4l2_subdev {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct csis_state {TYPE_1__ sd; int /*<<< orphan*/ * clock; } ;

/* Variables and functions */
 size_t CSIS_CLK_MUX ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5pcsis_clk_put (struct csis_state*) ; 
 int /*<<< orphan*/  s5pcsis_pm_suspend (int /*<<< orphan*/ *,int) ; 
 struct csis_state* sd_to_csis_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5pcsis_remove(struct platform_device *pdev)
{
	struct v4l2_subdev *sd = platform_get_drvdata(pdev);
	struct csis_state *state = sd_to_csis_state(sd);

	pm_runtime_disable(&pdev->dev);
	s5pcsis_pm_suspend(&pdev->dev, true);
	clk_disable(state->clock[CSIS_CLK_MUX]);
	pm_runtime_set_suspended(&pdev->dev);
	s5pcsis_clk_put(state);

	media_entity_cleanup(&state->sd.entity);

	return 0;
}