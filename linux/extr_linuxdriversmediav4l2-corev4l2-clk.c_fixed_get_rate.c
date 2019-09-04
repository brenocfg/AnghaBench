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
struct v4l2_clk_fixed {unsigned long rate; } ;
struct v4l2_clk {struct v4l2_clk_fixed* priv; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long fixed_get_rate(struct v4l2_clk *clk)
{
	struct v4l2_clk_fixed *priv = clk->priv;
	return priv->rate;
}