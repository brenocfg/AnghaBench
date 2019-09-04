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
struct delta_ctx {int aborting; int /*<<< orphan*/  name; struct delta_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void delta_job_abort(void *priv)
{
	struct delta_ctx *ctx = priv;
	struct delta_dev *delta = ctx->dev;

	dev_dbg(delta->dev, "%s aborting job\n", ctx->name);

	ctx->aborting = true;
}