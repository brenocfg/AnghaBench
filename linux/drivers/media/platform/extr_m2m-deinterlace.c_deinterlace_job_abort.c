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
struct deinterlace_dev {int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct deinterlace_ctx {int aborting; TYPE_1__ fh; struct deinterlace_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (struct deinterlace_dev*,char*) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void deinterlace_job_abort(void *priv)
{
	struct deinterlace_ctx *ctx = priv;
	struct deinterlace_dev *pcdev = ctx->dev;

	ctx->aborting = 1;

	dprintk(pcdev, "Aborting task\n");

	v4l2_m2m_job_finish(pcdev->m2m_dev, ctx->fh.m2m_ctx);
}