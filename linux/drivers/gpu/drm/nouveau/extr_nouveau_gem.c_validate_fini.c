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
struct validate_op {int /*<<< orphan*/  ticket; } ;
struct nouveau_fence {int dummy; } ;
struct nouveau_channel {int dummy; } ;
struct drm_nouveau_gem_pushbuf_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  validate_fini_no_ticket (struct validate_op*,struct nouveau_channel*,struct nouveau_fence*,struct drm_nouveau_gem_pushbuf_bo*) ; 
 int /*<<< orphan*/  ww_acquire_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
validate_fini(struct validate_op *op, struct nouveau_channel *chan,
	      struct nouveau_fence *fence,
	      struct drm_nouveau_gem_pushbuf_bo *pbbo)
{
	validate_fini_no_ticket(op, chan, fence, pbbo);
	ww_acquire_fini(&op->ticket);
}