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
struct ipu_csc_scaler_ctx {scalar_t__ icc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_image_convert_abort (scalar_t__) ; 

__attribute__((used)) static void job_abort(void *_ctx)
{
	struct ipu_csc_scaler_ctx *ctx = _ctx;

	if (ctx->icc)
		ipu_image_convert_abort(ctx->icc);
}