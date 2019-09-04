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
typedef  int /*<<< orphan*/  u32 ;
struct spu_context {TYPE_1__* ops; } ;
struct TYPE_2__ {size_t (* wbox_write ) (struct spu_context*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t stub1 (struct spu_context*,int /*<<< orphan*/ ) ; 

size_t spu_wbox_write(struct spu_context *ctx, u32 data)
{
	return ctx->ops->wbox_write(ctx, data);
}