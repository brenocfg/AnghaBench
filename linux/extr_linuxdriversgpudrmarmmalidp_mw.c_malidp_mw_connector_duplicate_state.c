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
struct drm_connector_state {int dummy; } ;
struct malidp_mw_connector_state {struct drm_connector_state base; int /*<<< orphan*/  rgb2yuv_initialized; int /*<<< orphan*/  rgb2yuv_coeffs; } ;
struct drm_connector {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __drm_atomic_helper_connector_duplicate_state (struct drm_connector*,struct drm_connector_state*) ; 
 struct malidp_mw_connector_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct malidp_mw_connector_state* to_mw_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_connector_state *
malidp_mw_connector_duplicate_state(struct drm_connector *connector)
{
	struct malidp_mw_connector_state *mw_state, *mw_current_state;

	if (WARN_ON(!connector->state))
		return NULL;

	mw_state = kzalloc(sizeof(*mw_state), GFP_KERNEL);
	if (!mw_state)
		return NULL;

	mw_current_state = to_mw_state(connector->state);
	mw_state->rgb2yuv_coeffs = mw_current_state->rgb2yuv_coeffs;
	mw_state->rgb2yuv_initialized = mw_current_state->rgb2yuv_initialized;

	__drm_atomic_helper_connector_duplicate_state(connector, &mw_state->base);

	return &mw_state->base;
}