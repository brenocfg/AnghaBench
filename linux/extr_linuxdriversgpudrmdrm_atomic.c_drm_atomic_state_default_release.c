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
struct drm_atomic_state {int /*<<< orphan*/  private_objs; int /*<<< orphan*/  planes; int /*<<< orphan*/  crtcs; int /*<<< orphan*/  connectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void drm_atomic_state_default_release(struct drm_atomic_state *state)
{
	kfree(state->connectors);
	kfree(state->crtcs);
	kfree(state->planes);
	kfree(state->private_objs);
}