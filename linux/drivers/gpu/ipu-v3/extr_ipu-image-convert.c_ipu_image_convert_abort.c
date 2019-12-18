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
struct ipu_image_convert_ctx {int aborting; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipu_image_convert_abort (struct ipu_image_convert_ctx*) ; 

void ipu_image_convert_abort(struct ipu_image_convert_ctx *ctx)
{
	__ipu_image_convert_abort(ctx);
	ctx->aborting = false;
}