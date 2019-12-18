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
struct v4l2_clk {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_clk_unregister (struct v4l2_clk*) ; 

void v4l2_clk_unregister_fixed(struct v4l2_clk *clk)
{
	kfree(clk->priv);
	v4l2_clk_unregister(clk);
}