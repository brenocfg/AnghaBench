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
struct drm_crtc {int /*<<< orphan*/  state; } ;
struct dpu_crtc_state {int dummy; } ;
typedef  enum dpu_crtc_client_type { ____Placeholder_dpu_crtc_client_type } dpu_crtc_client_type ;

/* Variables and functions */
 int NRT_CLIENT ; 
 int RT_CLIENT ; 
 struct dpu_crtc_state* to_dpu_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum dpu_crtc_client_type dpu_crtc_get_client_type(
						struct drm_crtc *crtc)
{
	struct dpu_crtc_state *cstate =
			crtc ? to_dpu_crtc_state(crtc->state) : NULL;

	if (!cstate)
		return NRT_CLIENT;

	return RT_CLIENT;
}