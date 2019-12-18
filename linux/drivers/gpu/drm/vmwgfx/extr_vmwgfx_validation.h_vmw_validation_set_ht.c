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
struct vmw_validation_context {struct drm_open_hash* ht; } ;
struct drm_open_hash {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void vmw_validation_set_ht(struct vmw_validation_context *ctx,
					 struct drm_open_hash *ht)
{
	ctx->ht = ht;
}