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
struct drm_atomic_state {int dummy; } ;
struct nv50_atom {struct drm_atomic_state state; int /*<<< orphan*/  outp; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ drm_atomic_state_init (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  kfree (struct nv50_atom*) ; 
 struct nv50_atom* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_atomic_state *
nv50_disp_atomic_state_alloc(struct drm_device *dev)
{
	struct nv50_atom *atom;
	if (!(atom = kzalloc(sizeof(*atom), GFP_KERNEL)) ||
	    drm_atomic_state_init(dev, &atom->state) < 0) {
		kfree(atom);
		return NULL;
	}
	INIT_LIST_HEAD(&atom->outp);
	return &atom->state;
}