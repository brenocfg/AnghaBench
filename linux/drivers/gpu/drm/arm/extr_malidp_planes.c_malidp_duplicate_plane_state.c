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
struct drm_plane_state {int dummy; } ;
struct malidp_plane_state {struct drm_plane_state base; int /*<<< orphan*/  mmu_prefetch_pgsize; int /*<<< orphan*/  mmu_prefetch_mode; int /*<<< orphan*/  n_planes; int /*<<< orphan*/  format; int /*<<< orphan*/  rotmem_size; } ;
struct drm_plane {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_duplicate_state (struct drm_plane*,struct drm_plane_state*) ; 
 struct malidp_plane_state* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct malidp_plane_state* to_malidp_plane_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct
drm_plane_state *malidp_duplicate_plane_state(struct drm_plane *plane)
{
	struct malidp_plane_state *state, *m_state;

	if (!plane->state)
		return NULL;

	state = kmalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return NULL;

	m_state = to_malidp_plane_state(plane->state);
	__drm_atomic_helper_plane_duplicate_state(plane, &state->base);
	state->rotmem_size = m_state->rotmem_size;
	state->format = m_state->format;
	state->n_planes = m_state->n_planes;

	state->mmu_prefetch_mode = m_state->mmu_prefetch_mode;
	state->mmu_prefetch_pgsize = m_state->mmu_prefetch_pgsize;

	return &state->base;
}