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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct ocxl_context {int /*<<< orphan*/  xsl_error_lock; TYPE_1__ xsl_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool has_xsl_error(struct ocxl_context *ctx)
{
	bool ret;

	mutex_lock(&ctx->xsl_error_lock);
	ret = !!ctx->xsl_error.addr;
	mutex_unlock(&ctx->xsl_error_lock);

	return ret;
}