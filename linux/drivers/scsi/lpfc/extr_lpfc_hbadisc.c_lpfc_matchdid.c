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
typedef  scalar_t__ uint32_t ;
struct lpfc_vport {scalar_t__ fc_myDID; TYPE_1__* phba; } ;
struct lpfc_nodelist {scalar_t__ nlp_DID; } ;
struct TYPE_6__ {scalar_t__ domain; scalar_t__ area; scalar_t__ id; } ;
struct TYPE_7__ {scalar_t__ word; TYPE_2__ b; } ;
struct TYPE_8__ {TYPE_3__ un; } ;
struct TYPE_5__ {scalar_t__ fc_topology; } ;
typedef  TYPE_4__ D_ID ;

/* Variables and functions */
 scalar_t__ Bcast_DID ; 
 scalar_t__ LPFC_TOPOLOGY_LOOP ; 

__attribute__((used)) static int
lpfc_matchdid(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
	      uint32_t did)
{
	D_ID mydid, ndlpdid, matchdid;

	if (did == Bcast_DID)
		return 0;

	/* First check for Direct match */
	if (ndlp->nlp_DID == did)
		return 1;

	/* Next check for area/domain identically equals 0 match */
	mydid.un.word = vport->fc_myDID;
	if ((mydid.un.b.domain == 0) && (mydid.un.b.area == 0)) {
		return 0;
	}

	matchdid.un.word = did;
	ndlpdid.un.word = ndlp->nlp_DID;
	if (matchdid.un.b.id == ndlpdid.un.b.id) {
		if ((mydid.un.b.domain == matchdid.un.b.domain) &&
		    (mydid.un.b.area == matchdid.un.b.area)) {
			/* This code is supposed to match the ID
			 * for a private loop device that is
			 * connect to fl_port. But we need to
			 * check that the port did not just go
			 * from pt2pt to fabric or we could end
			 * up matching ndlp->nlp_DID 000001 to
			 * fabric DID 0x20101
			 */
			if ((ndlpdid.un.b.domain == 0) &&
			    (ndlpdid.un.b.area == 0)) {
				if (ndlpdid.un.b.id &&
				    vport->phba->fc_topology ==
				    LPFC_TOPOLOGY_LOOP)
					return 1;
			}
			return 0;
		}

		matchdid.un.word = ndlp->nlp_DID;
		if ((mydid.un.b.domain == ndlpdid.un.b.domain) &&
		    (mydid.un.b.area == ndlpdid.un.b.area)) {
			if ((matchdid.un.b.domain == 0) &&
			    (matchdid.un.b.area == 0)) {
				if (matchdid.un.b.id)
					return 1;
			}
		}
	}
	return 0;
}