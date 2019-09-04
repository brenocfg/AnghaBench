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
struct emmaprp_dev {int /*<<< orphan*/  m2m_dev; } ;
struct emmaprp_ctx {int aborting; int /*<<< orphan*/  m2m_ctx; struct emmaprp_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (struct emmaprp_dev*,char*) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emmaprp_job_abort(void *priv)
{
	struct emmaprp_ctx *ctx = priv;
	struct emmaprp_dev *pcdev = ctx->dev;

	ctx->aborting = 1;

	dprintk(pcdev, "Aborting task\n");

	v4l2_m2m_job_finish(pcdev->m2m_dev, ctx->m2m_ctx);
}