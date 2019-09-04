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
struct nv50_mstc {TYPE_2__* mstm; } ;
struct TYPE_6__ {size_t index; } ;
struct nv50_head {TYPE_3__ base; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector_state {int /*<<< orphan*/  crtc; } ;
struct drm_connector {int dummy; } ;
struct TYPE_5__ {TYPE_1__** msto; } ;
struct TYPE_4__ {struct drm_encoder encoder; } ;

/* Variables and functions */
 struct nv50_head* nv50_head (int /*<<< orphan*/ ) ; 
 struct nv50_mstc* nv50_mstc (struct drm_connector*) ; 

__attribute__((used)) static struct drm_encoder *
nv50_mstc_atomic_best_encoder(struct drm_connector *connector,
			      struct drm_connector_state *connector_state)
{
	struct nv50_head *head = nv50_head(connector_state->crtc);
	struct nv50_mstc *mstc = nv50_mstc(connector);

	return &mstc->mstm->msto[head->base.index]->encoder;
}