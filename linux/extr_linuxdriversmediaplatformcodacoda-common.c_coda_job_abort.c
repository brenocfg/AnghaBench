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
struct coda_ctx {int aborting; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  coda_debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void coda_job_abort(void *priv)
{
	struct coda_ctx *ctx = priv;

	ctx->aborting = 1;

	v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev,
		 "Aborting task\n");
}