#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct nv50_msto {TYPE_3__ encoder; struct nv50_mstc* mstc; } ;
struct TYPE_14__ {int max_payloads; struct drm_dp_payload* payloads; int /*<<< orphan*/  payload_lock; } ;
struct nv50_mstm {TYPE_7__ mgr; TYPE_6__* outp; } ;
struct nv50_mstc {TYPE_2__* port; struct nv50_mstm* mstm; } ;
struct nouveau_drm {int dummy; } ;
struct drm_dp_payload {int vcpi; int /*<<< orphan*/  num_slots; int /*<<< orphan*/  start_slot; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_12__ {TYPE_4__ base; } ;
struct TYPE_13__ {TYPE_5__ base; } ;
struct TYPE_8__ {int vcpi; } ;
struct TYPE_9__ {TYPE_1__ vcpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_ATOMIC (struct nouveau_drm*,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_dp_payload *
nv50_msto_payload(struct nv50_msto *msto)
{
	struct nouveau_drm *drm = nouveau_drm(msto->encoder.dev);
	struct nv50_mstc *mstc = msto->mstc;
	struct nv50_mstm *mstm = mstc->mstm;
	int vcpi = mstc->port->vcpi.vcpi, i;

	WARN_ON(!mutex_is_locked(&mstm->mgr.payload_lock));

	NV_ATOMIC(drm, "%s: vcpi %d\n", msto->encoder.name, vcpi);
	for (i = 0; i < mstm->mgr.max_payloads; i++) {
		struct drm_dp_payload *payload = &mstm->mgr.payloads[i];
		NV_ATOMIC(drm, "%s: %d: vcpi %d start 0x%02x slots 0x%02x\n",
			  mstm->outp->base.base.name, i, payload->vcpi,
			  payload->start_slot, payload->num_slots);
	}

	for (i = 0; i < mstm->mgr.max_payloads; i++) {
		struct drm_dp_payload *payload = &mstm->mgr.payloads[i];
		if (payload->vcpi == vcpi)
			return payload;
	}

	return NULL;
}