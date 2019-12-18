#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct cedrus_ctx {TYPE_2__** ctrls; } ;
struct TYPE_3__ {void* p; } ;
struct TYPE_4__ {scalar_t__ id; TYPE_1__ p_cur; } ;

/* Variables and functions */

void *cedrus_find_control_data(struct cedrus_ctx *ctx, u32 id)
{
	unsigned int i;

	for (i = 0; ctx->ctrls[i]; i++)
		if (ctx->ctrls[i]->id == id)
			return ctx->ctrls[i]->p_cur.p;

	return NULL;
}