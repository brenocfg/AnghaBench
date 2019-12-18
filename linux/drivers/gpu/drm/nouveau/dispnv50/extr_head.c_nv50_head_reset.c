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
struct nv50_head_atom {int /*<<< orphan*/  state; } ;
struct drm_crtc {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_reset (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 struct nv50_head_atom* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_head_atomic_destroy_state (struct drm_crtc*,scalar_t__) ; 

__attribute__((used)) static void
nv50_head_reset(struct drm_crtc *crtc)
{
	struct nv50_head_atom *asyh;

	if (WARN_ON(!(asyh = kzalloc(sizeof(*asyh), GFP_KERNEL))))
		return;

	if (crtc->state)
		nv50_head_atomic_destroy_state(crtc, crtc->state);

	__drm_atomic_helper_crtc_reset(crtc, &asyh->state);
}