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
struct csi2rx_priv {unsigned int max_streams; int /*<<< orphan*/  dev; int /*<<< orphan*/  source_subdev; int /*<<< orphan*/  p_clk; int /*<<< orphan*/ * pixel_clk; scalar_t__ base; int /*<<< orphan*/  sys_clk; } ;

/* Variables and functions */
 scalar_t__ CSI2RX_STREAM_CTRL_REG (unsigned int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  s_stream ; 
 scalar_t__ v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void csi2rx_stop(struct csi2rx_priv *csi2rx)
{
	unsigned int i;

	clk_prepare_enable(csi2rx->p_clk);
	clk_disable_unprepare(csi2rx->sys_clk);

	for (i = 0; i < csi2rx->max_streams; i++) {
		writel(0, csi2rx->base + CSI2RX_STREAM_CTRL_REG(i));

		clk_disable_unprepare(csi2rx->pixel_clk[i]);
	}

	clk_disable_unprepare(csi2rx->p_clk);

	if (v4l2_subdev_call(csi2rx->source_subdev, video, s_stream, false))
		dev_warn(csi2rx->dev, "Couldn't disable our subdev\n");
}