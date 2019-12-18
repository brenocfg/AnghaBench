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
struct nv50_msto {int disabled; TYPE_2__* head; struct nv50_mstc* mstc; } ;
struct nv50_mstm {int modified; int disabled; int /*<<< orphan*/  links; TYPE_3__* outp; int /*<<< orphan*/  mgr; } ;
struct nv50_mstc {int /*<<< orphan*/  port; struct nv50_mstm* mstm; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* update ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dp_mst_reset_vcpi_slots (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nv50_msto* nv50_msto (struct drm_encoder*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv50_msto_disable(struct drm_encoder *encoder)
{
	struct nv50_msto *msto = nv50_msto(encoder);
	struct nv50_mstc *mstc = msto->mstc;
	struct nv50_mstm *mstm = mstc->mstm;

	drm_dp_mst_reset_vcpi_slots(&mstm->mgr, mstc->port);

	mstm->outp->update(mstm->outp, msto->head->base.index, NULL, 0, 0);
	mstm->modified = true;
	if (!--mstm->links)
		mstm->disabled = true;
	msto->disabled = true;
}