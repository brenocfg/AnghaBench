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
struct hva_ctx {int aborting; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hva_job_abort(void *priv)
{
	struct hva_ctx *ctx = priv;
	struct device *dev = ctx_to_dev(ctx);

	dev_dbg(dev, "%s aborting job\n", ctx->name);

	ctx->aborting = true;
}