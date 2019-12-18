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
struct drm_plane_state {int dummy; } ;
struct TYPE_4__ {scalar_t__ mask; } ;
struct TYPE_3__ {scalar_t__ mask; } ;
struct nv50_wndw_atom {struct drm_plane_state state; TYPE_2__ set; TYPE_1__ clr; int /*<<< orphan*/  point; int /*<<< orphan*/  image; int /*<<< orphan*/  csc; int /*<<< orphan*/  xlut; int /*<<< orphan*/ * ilut; int /*<<< orphan*/  ntfy; int /*<<< orphan*/  sema; } ;
struct drm_plane {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_duplicate_state (struct drm_plane*,struct drm_plane_state*) ; 
 struct nv50_wndw_atom* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct nv50_wndw_atom* nv50_wndw_atom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_plane_state *
nv50_wndw_atomic_duplicate_state(struct drm_plane *plane)
{
	struct nv50_wndw_atom *armw = nv50_wndw_atom(plane->state);
	struct nv50_wndw_atom *asyw;
	if (!(asyw = kmalloc(sizeof(*asyw), GFP_KERNEL)))
		return NULL;
	__drm_atomic_helper_plane_duplicate_state(plane, &asyw->state);
	asyw->sema = armw->sema;
	asyw->ntfy = armw->ntfy;
	asyw->ilut = NULL;
	asyw->xlut = armw->xlut;
	asyw->csc  = armw->csc;
	asyw->image = armw->image;
	asyw->point = armw->point;
	asyw->clr.mask = 0;
	asyw->set.mask = 0;
	return &asyw->state;
}