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
struct coda_ctx {TYPE_1__* internal_frames; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int CODA_MAX_FRAMEBUFFERS ; 
 int /*<<< orphan*/  coda_free_aux_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void coda_free_framebuffers(struct coda_ctx *ctx)
{
	int i;

	for (i = 0; i < CODA_MAX_FRAMEBUFFERS; i++)
		coda_free_aux_buf(ctx->dev, &ctx->internal_frames[i].buf);
}