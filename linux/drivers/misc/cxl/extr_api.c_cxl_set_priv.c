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
struct cxl_context {void* priv; } ;

/* Variables and functions */
 int EINVAL ; 

int cxl_set_priv(struct cxl_context *ctx, void *priv)
{
	if (!ctx)
		return -EINVAL;

	ctx->priv = priv;

	return 0;
}