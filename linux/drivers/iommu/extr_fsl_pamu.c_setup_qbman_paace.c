#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  coherency_required; } ;
struct TYPE_6__ {TYPE_1__ to_host; } ;
struct TYPE_8__ {int /*<<< orphan*/  omi; } ;
struct TYPE_7__ {TYPE_4__ index_ot; } ;
struct paace {TYPE_2__ domain_attr; int /*<<< orphan*/  impl_attr; TYPE_3__ op_encode; } ;

/* Variables and functions */
#define  BMAN_PAACE 130 
 int /*<<< orphan*/  OMI_QMAN ; 
 int /*<<< orphan*/  OMI_QMAN_PRIV ; 
 int /*<<< orphan*/  PAACE_DA_HOST_CR ; 
 int /*<<< orphan*/  PAACE_IA_CID ; 
 int /*<<< orphan*/  PAACE_IA_OTM ; 
 int /*<<< orphan*/  PAACE_OTM_INDEXED ; 
 int /*<<< orphan*/  PAMU_ATTR_CACHE_L3 ; 
#define  QMAN_PAACE 129 
#define  QMAN_PORTAL_PAACE 128 
 int /*<<< orphan*/  get_stash_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_qbman_paace(struct paace *ppaace, int  paace_type)
{
	switch (paace_type) {
	case QMAN_PAACE:
		set_bf(ppaace->impl_attr, PAACE_IA_OTM, PAACE_OTM_INDEXED);
		ppaace->op_encode.index_ot.omi = OMI_QMAN_PRIV;
		/* setup QMAN Private data stashing for the L3 cache */
		set_bf(ppaace->impl_attr, PAACE_IA_CID, get_stash_id(PAMU_ATTR_CACHE_L3, 0));
		set_bf(ppaace->domain_attr.to_host.coherency_required, PAACE_DA_HOST_CR,
		       0);
		break;
	case QMAN_PORTAL_PAACE:
		set_bf(ppaace->impl_attr, PAACE_IA_OTM, PAACE_OTM_INDEXED);
		ppaace->op_encode.index_ot.omi = OMI_QMAN;
		/* Set DQRR and Frame stashing for the L3 cache */
		set_bf(ppaace->impl_attr, PAACE_IA_CID, get_stash_id(PAMU_ATTR_CACHE_L3, 0));
		break;
	case BMAN_PAACE:
		set_bf(ppaace->domain_attr.to_host.coherency_required, PAACE_DA_HOST_CR,
		       0);
		break;
	}
}