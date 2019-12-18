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
struct drm_private_state {int dummy; } ;
struct drm_private_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  priv_to_comp_st (struct drm_private_state*) ; 
 int /*<<< orphan*/  to_improc_st (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
komeda_improc_atomic_destroy_state(struct drm_private_obj *obj,
				   struct drm_private_state *state)
{
	kfree(to_improc_st(priv_to_comp_st(state)));
}