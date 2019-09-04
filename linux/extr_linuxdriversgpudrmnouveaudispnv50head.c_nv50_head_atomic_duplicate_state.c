#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_crtc_state {int dummy; } ;
struct TYPE_4__ {scalar_t__ mask; } ;
struct TYPE_3__ {scalar_t__ mask; } ;
struct nv50_head_atom {struct drm_crtc_state state; TYPE_2__ set; TYPE_1__ clr; int /*<<< orphan*/  procamp; int /*<<< orphan*/  dither; int /*<<< orphan*/  ovly; int /*<<< orphan*/  base; int /*<<< orphan*/  curs; int /*<<< orphan*/  core; int /*<<< orphan*/  olut; int /*<<< orphan*/  mode; int /*<<< orphan*/  view; int /*<<< orphan*/  wndw; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_duplicate_state (struct drm_crtc*,struct drm_crtc_state*) ; 
 struct nv50_head_atom* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct nv50_head_atom* nv50_head_atom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_crtc_state *
nv50_head_atomic_duplicate_state(struct drm_crtc *crtc)
{
	struct nv50_head_atom *armh = nv50_head_atom(crtc->state);
	struct nv50_head_atom *asyh;
	if (!(asyh = kmalloc(sizeof(*asyh), GFP_KERNEL)))
		return NULL;
	__drm_atomic_helper_crtc_duplicate_state(crtc, &asyh->state);
	asyh->wndw = armh->wndw;
	asyh->view = armh->view;
	asyh->mode = armh->mode;
	asyh->olut = armh->olut;
	asyh->core = armh->core;
	asyh->curs = armh->curs;
	asyh->base = armh->base;
	asyh->ovly = armh->ovly;
	asyh->dither = armh->dither;
	asyh->procamp = armh->procamp;
	asyh->clr.mask = 0;
	asyh->set.mask = 0;
	return &asyh->state;
}