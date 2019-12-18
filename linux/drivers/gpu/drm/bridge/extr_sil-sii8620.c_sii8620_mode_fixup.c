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
struct sii8620 {int /*<<< orphan*/  lock; int /*<<< orphan*/  use_packed_pixel; } ;
struct drm_display_mode {int dummy; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct sii8620* bridge_to_sii8620 (struct drm_bridge*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sii8620_is_packing_required (struct sii8620*,struct drm_display_mode*) ; 

__attribute__((used)) static bool sii8620_mode_fixup(struct drm_bridge *bridge,
			       const struct drm_display_mode *mode,
			       struct drm_display_mode *adjusted_mode)
{
	struct sii8620 *ctx = bridge_to_sii8620(bridge);

	mutex_lock(&ctx->lock);

	ctx->use_packed_pixel = sii8620_is_packing_required(ctx, adjusted_mode);

	mutex_unlock(&ctx->lock);

	return true;
}