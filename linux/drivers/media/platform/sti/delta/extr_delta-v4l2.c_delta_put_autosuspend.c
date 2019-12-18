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
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct delta_ctx {struct delta_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

void delta_put_autosuspend(struct delta_ctx *ctx)
{
	struct delta_dev *delta = ctx->dev;

	pm_runtime_put_autosuspend(delta->dev);
}