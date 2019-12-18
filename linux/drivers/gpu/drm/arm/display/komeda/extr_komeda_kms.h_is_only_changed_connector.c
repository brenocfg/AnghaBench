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
typedef  int u32 ;
struct drm_crtc_state {int connector_mask; int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 struct drm_crtc_state* drm_atomic_get_old_crtc_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_index (struct drm_connector*) ; 

__attribute__((used)) static inline bool
is_only_changed_connector(struct drm_crtc_state *st, struct drm_connector *conn)
{
	struct drm_crtc_state *old_st;
	u32 changed_connectors;

	old_st = drm_atomic_get_old_crtc_state(st->state, st->crtc);
	changed_connectors = st->connector_mask ^ old_st->connector_mask;

	return BIT(drm_connector_index(conn)) == changed_connectors;
}