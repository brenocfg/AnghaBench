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
struct vmw_resource {TYPE_1__* backup; } ;
struct ttm_validate_buffer {int /*<<< orphan*/ * bo; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int vmw_cotable_unscrub (struct vmw_resource*) ; 

__attribute__((used)) static int vmw_cotable_bind(struct vmw_resource *res,
			    struct ttm_validate_buffer *val_buf)
{
	/*
	 * The create() callback may have changed @res->backup without
	 * the caller noticing, and with val_buf->bo still pointing to
	 * the old backup buffer. Although hackish, and not used currently,
	 * take the opportunity to correct the value here so that it's not
	 * misused in the future.
	 */
	val_buf->bo = &res->backup->base;

	return vmw_cotable_unscrub(res);
}