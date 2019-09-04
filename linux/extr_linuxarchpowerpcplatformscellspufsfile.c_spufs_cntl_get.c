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
typedef  int /*<<< orphan*/  u64 ;
struct spu_context {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* status_read ) (struct spu_context*) ;} ;

/* Variables and functions */
 int spu_acquire (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 int /*<<< orphan*/  stub1 (struct spu_context*) ; 

__attribute__((used)) static int spufs_cntl_get(void *data, u64 *val)
{
	struct spu_context *ctx = data;
	int ret;

	ret = spu_acquire(ctx);
	if (ret)
		return ret;
	*val = ctx->ops->status_read(ctx);
	spu_release(ctx);

	return 0;
}