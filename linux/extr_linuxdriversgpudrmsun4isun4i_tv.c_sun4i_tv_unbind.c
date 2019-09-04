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
struct sun4i_tv {int /*<<< orphan*/  clk; int /*<<< orphan*/  encoder; int /*<<< orphan*/  connector; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sun4i_tv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sun4i_tv_unbind(struct device *dev, struct device *master,
			    void *data)
{
	struct sun4i_tv *tv = dev_get_drvdata(dev);

	drm_connector_cleanup(&tv->connector);
	drm_encoder_cleanup(&tv->encoder);
	clk_disable_unprepare(tv->clk);
}