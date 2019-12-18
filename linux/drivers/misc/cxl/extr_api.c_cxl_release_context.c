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
struct cxl_context {scalar_t__ status; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ STARTED ; 
 int /*<<< orphan*/  cxl_context_free (struct cxl_context*) ; 

int cxl_release_context(struct cxl_context *ctx)
{
	if (ctx->status >= STARTED)
		return -EBUSY;

	cxl_context_free(ctx);

	return 0;
}