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
struct drm_i915_file_private {int /*<<< orphan*/  ban_score; } ;

/* Variables and functions */
 scalar_t__ I915_CLIENT_SCORE_BANNED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool client_is_banned(struct drm_i915_file_private *file_priv)
{
	return atomic_read(&file_priv->ban_score) >= I915_CLIENT_SCORE_BANNED;
}