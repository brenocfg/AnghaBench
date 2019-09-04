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
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct nv50_msto {int disabled; int /*<<< orphan*/ * head; struct nv50_mstc* mstc; TYPE_2__ encoder; } ;
struct nv50_mstm {int /*<<< orphan*/  mgr; } ;
struct nv50_mstc {TYPE_3__* port; struct nv50_mstm* mstm; } ;
struct nouveau_drm {int dummy; } ;
struct TYPE_4__ {scalar_t__ vcpi; } ;
struct TYPE_6__ {TYPE_1__ vcpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_ATOMIC (struct nouveau_drm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_mst_deallocate_vcpi (int /*<<< orphan*/ *,TYPE_3__*) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_msto_payload (struct nv50_msto*) ; 

__attribute__((used)) static void
nv50_msto_cleanup(struct nv50_msto *msto)
{
	struct nouveau_drm *drm = nouveau_drm(msto->encoder.dev);
	struct nv50_mstc *mstc = msto->mstc;
	struct nv50_mstm *mstm = mstc->mstm;

	NV_ATOMIC(drm, "%s: msto cleanup\n", msto->encoder.name);
	if (mstc->port && mstc->port->vcpi.vcpi > 0 && !nv50_msto_payload(msto))
		drm_dp_mst_deallocate_vcpi(&mstm->mgr, mstc->port);
	if (msto->disabled) {
		msto->mstc = NULL;
		msto->head = NULL;
		msto->disabled = false;
	}
}