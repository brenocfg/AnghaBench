#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct bfi_sfp_scn_s {int event; scalar_t__ pomlvl; scalar_t__ sfpid; } ;
struct bfad_s {int dummy; } ;
struct bfa_sfp_s {TYPE_5__* ioc; } ;
struct TYPE_9__ {scalar_t__ level; int /*<<< orphan*/  mac; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  ioc_type; } ;
struct TYPE_10__ {TYPE_3__ port; } ;
struct bfa_aen_entry_s {TYPE_4__ aen_data; } ;
typedef  enum bfa_port_aen_event { ____Placeholder_bfa_port_aen_event } bfa_port_aen_event ;
struct TYPE_11__ {int /*<<< orphan*/  ioc_aen_seq; TYPE_2__* attr; TYPE_1__* bfa; } ;
struct TYPE_8__ {int /*<<< orphan*/  pwwn; } ;
struct TYPE_7__ {scalar_t__ bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_AEN_CAT_PORT ; 
 int BFA_PORT_AEN_SFP_ACCESS_ERROR ; 
 int BFA_PORT_AEN_SFP_INSERT ; 
 int BFA_PORT_AEN_SFP_POM ; 
 int BFA_PORT_AEN_SFP_REMOVE ; 
 int BFA_PORT_AEN_SFP_UNSUPPORT ; 
#define  BFA_SFP_SCN_FAILED 132 
#define  BFA_SFP_SCN_INSERTED 131 
#define  BFA_SFP_SCN_POM 130 
#define  BFA_SFP_SCN_REMOVED 129 
#define  BFA_SFP_SCN_UNSUPPORT 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_ioc_get_mac (TYPE_5__*) ; 
 int /*<<< orphan*/  bfa_ioc_get_type (TYPE_5__*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_sfp_s*,int) ; 
 int /*<<< orphan*/  bfad_get_aen_entry (struct bfad_s*,struct bfa_aen_entry_s*) ; 
 int /*<<< orphan*/  bfad_im_post_vendor_event (struct bfa_aen_entry_s*,struct bfad_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_sfp_scn_aen_post(struct bfa_sfp_s *sfp, struct bfi_sfp_scn_s *rsp)
{
	struct bfad_s *bfad = (struct bfad_s *)sfp->ioc->bfa->bfad;
	struct bfa_aen_entry_s  *aen_entry;
	enum bfa_port_aen_event aen_evt = 0;

	bfa_trc(sfp, (((u64)rsp->pomlvl) << 16) | (((u64)rsp->sfpid) << 8) |
		      ((u64)rsp->event));

	bfad_get_aen_entry(bfad, aen_entry);
	if (!aen_entry)
		return;

	aen_entry->aen_data.port.ioc_type = bfa_ioc_get_type(sfp->ioc);
	aen_entry->aen_data.port.pwwn = sfp->ioc->attr->pwwn;
	aen_entry->aen_data.port.mac = bfa_ioc_get_mac(sfp->ioc);

	switch (rsp->event) {
	case BFA_SFP_SCN_INSERTED:
		aen_evt = BFA_PORT_AEN_SFP_INSERT;
		break;
	case BFA_SFP_SCN_REMOVED:
		aen_evt = BFA_PORT_AEN_SFP_REMOVE;
		break;
	case BFA_SFP_SCN_FAILED:
		aen_evt = BFA_PORT_AEN_SFP_ACCESS_ERROR;
		break;
	case BFA_SFP_SCN_UNSUPPORT:
		aen_evt = BFA_PORT_AEN_SFP_UNSUPPORT;
		break;
	case BFA_SFP_SCN_POM:
		aen_evt = BFA_PORT_AEN_SFP_POM;
		aen_entry->aen_data.port.level = rsp->pomlvl;
		break;
	default:
		bfa_trc(sfp, rsp->event);
		WARN_ON(1);
	}

	/* Send the AEN notification */
	bfad_im_post_vendor_event(aen_entry, bfad, ++sfp->ioc->ioc_aen_seq,
				  BFA_AEN_CAT_PORT, aen_evt);
}