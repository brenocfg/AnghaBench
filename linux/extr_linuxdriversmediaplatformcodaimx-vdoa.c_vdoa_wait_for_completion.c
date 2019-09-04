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
struct vdoa_data {int /*<<< orphan*/  dev; } ;
struct vdoa_ctx {scalar_t__ submitted_job; scalar_t__ completed_job; int /*<<< orphan*/  completion; struct vdoa_data* vdoa; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int vdoa_wait_for_completion(struct vdoa_ctx *ctx)
{
	struct vdoa_data *vdoa = ctx->vdoa;

	if (ctx->submitted_job == ctx->completed_job)
		return 0;

	if (!wait_for_completion_timeout(&ctx->completion,
					 msecs_to_jiffies(300))) {
		dev_err(vdoa->dev,
			"Timeout waiting for transfer result\n");
		return -ETIMEDOUT;
	}

	return 0;
}