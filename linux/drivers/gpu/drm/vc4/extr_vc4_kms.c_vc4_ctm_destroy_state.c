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
struct vc4_ctm_state {int dummy; } ;
struct drm_private_state {int dummy; } ;
struct drm_private_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vc4_ctm_state*) ; 
 struct vc4_ctm_state* to_vc4_ctm_state (struct drm_private_state*) ; 

__attribute__((used)) static void vc4_ctm_destroy_state(struct drm_private_obj *obj,
				  struct drm_private_state *state)
{
	struct vc4_ctm_state *ctm_state = to_vc4_ctm_state(state);

	kfree(ctm_state);
}