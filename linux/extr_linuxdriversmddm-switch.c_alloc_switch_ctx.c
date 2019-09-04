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
struct switch_path {int dummy; } ;
struct switch_ctx {unsigned int region_size; struct dm_target* ti; } ;
struct dm_target {struct switch_ctx* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct switch_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct switch_ctx *alloc_switch_ctx(struct dm_target *ti, unsigned nr_paths,
					   unsigned region_size)
{
	struct switch_ctx *sctx;

	sctx = kzalloc(sizeof(struct switch_ctx) + nr_paths * sizeof(struct switch_path),
		       GFP_KERNEL);
	if (!sctx)
		return NULL;

	sctx->ti = ti;
	sctx->region_size = region_size;

	ti->private = sctx;

	return sctx;
}