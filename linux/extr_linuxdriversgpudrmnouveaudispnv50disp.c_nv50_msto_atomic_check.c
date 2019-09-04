#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nv50_mstm {int /*<<< orphan*/  mgr; } ;
struct nv50_mstc {int /*<<< orphan*/  native; int /*<<< orphan*/  pbn; struct nv50_mstm* mstm; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  clock; } ;
struct drm_crtc_state {TYPE_1__ adjusted_mode; } ;
struct drm_connector_state {TYPE_3__* connector; } ;
struct TYPE_5__ {int bpc; } ;
struct TYPE_6__ {TYPE_2__ display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dp_calc_pbn_mode (int /*<<< orphan*/ ,int) ; 
 int drm_dp_find_vcpi_slots (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nv50_mstc* nv50_mstc (TYPE_3__*) ; 
 int nv50_outp_atomic_check_view (struct drm_encoder*,struct drm_crtc_state*,struct drm_connector_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv50_msto_atomic_check(struct drm_encoder *encoder,
		       struct drm_crtc_state *crtc_state,
		       struct drm_connector_state *conn_state)
{
	struct nv50_mstc *mstc = nv50_mstc(conn_state->connector);
	struct nv50_mstm *mstm = mstc->mstm;
	int bpp = conn_state->connector->display_info.bpc * 3;
	int slots;

	mstc->pbn = drm_dp_calc_pbn_mode(crtc_state->adjusted_mode.clock, bpp);

	slots = drm_dp_find_vcpi_slots(&mstm->mgr, mstc->pbn);
	if (slots < 0)
		return slots;

	return nv50_outp_atomic_check_view(encoder, crtc_state, conn_state,
					   mstc->native);
}