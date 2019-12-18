#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_13__ {int feaLevelHigh; } ;
struct TYPE_16__ {TYPE_3__ rev; } ;
struct lpfc_hba {int cfg_topology; int /*<<< orphan*/  fc_pref_ALPA; TYPE_6__ vpd; TYPE_2__* pcidev; } ;
typedef  TYPE_6__ lpfc_vpd_t ;
struct TYPE_14__ {int link_flags; int /*<<< orphan*/  fabric_AL_PA; void* link_speed; } ;
struct TYPE_15__ {TYPE_4__ varInitLnk; } ;
struct TYPE_17__ {TYPE_5__ un; int /*<<< orphan*/  mbxOwner; scalar_t__ mbxCommand; } ;
struct TYPE_11__ {TYPE_7__ mb; } ;
struct TYPE_18__ {TYPE_1__ u; } ;
struct TYPE_12__ {scalar_t__ device; } ;
typedef  TYPE_7__ MAILBOX_t ;
typedef  TYPE_8__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FLAGS_IMED_ABORT ; 
 int FLAGS_LINK_SPEED ; 
#define  FLAGS_LOCAL_LB 141 
 int FLAGS_TOPOLOGY_FAILOVER ; 
#define  FLAGS_TOPOLOGY_MODE_LOOP 140 
#define  FLAGS_TOPOLOGY_MODE_LOOP_PT 139 
#define  FLAGS_TOPOLOGY_MODE_PT_LOOP 138 
#define  FLAGS_TOPOLOGY_MODE_PT_PT 137 
 void* LINK_SPEED_10G ; 
 void* LINK_SPEED_16G ; 
 void* LINK_SPEED_1G ; 
 void* LINK_SPEED_2G ; 
 void* LINK_SPEED_32G ; 
 void* LINK_SPEED_4G ; 
 void* LINK_SPEED_64G ; 
 void* LINK_SPEED_8G ; 
 void* LINK_SPEED_AUTO ; 
#define  LPFC_USER_LINK_SPEED_10G 136 
#define  LPFC_USER_LINK_SPEED_16G 135 
#define  LPFC_USER_LINK_SPEED_1G 134 
#define  LPFC_USER_LINK_SPEED_2G 133 
#define  LPFC_USER_LINK_SPEED_32G 132 
#define  LPFC_USER_LINK_SPEED_4G 131 
#define  LPFC_USER_LINK_SPEED_64G 130 
#define  LPFC_USER_LINK_SPEED_8G 129 
#define  LPFC_USER_LINK_SPEED_AUTO 128 
 scalar_t__ MBX_INIT_LINK ; 
 int /*<<< orphan*/  OWN_HOST ; 
 scalar_t__ PCI_DEVICE_ID_LANCER_G6_FC ; 
 scalar_t__ PCI_DEVICE_ID_LANCER_G7_FC ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 

void
lpfc_init_link(struct lpfc_hba * phba,
	       LPFC_MBOXQ_t * pmb, uint32_t topology, uint32_t linkspeed)
{
	lpfc_vpd_t *vpd;
	MAILBOX_t *mb;

	mb = &pmb->u.mb;
	memset(pmb, 0, sizeof (LPFC_MBOXQ_t));

	switch (topology) {
	case FLAGS_TOPOLOGY_MODE_LOOP_PT:
		mb->un.varInitLnk.link_flags = FLAGS_TOPOLOGY_MODE_LOOP;
		mb->un.varInitLnk.link_flags |= FLAGS_TOPOLOGY_FAILOVER;
		break;
	case FLAGS_TOPOLOGY_MODE_PT_PT:
		mb->un.varInitLnk.link_flags = FLAGS_TOPOLOGY_MODE_PT_PT;
		break;
	case FLAGS_TOPOLOGY_MODE_LOOP:
		mb->un.varInitLnk.link_flags = FLAGS_TOPOLOGY_MODE_LOOP;
		break;
	case FLAGS_TOPOLOGY_MODE_PT_LOOP:
		mb->un.varInitLnk.link_flags = FLAGS_TOPOLOGY_MODE_PT_PT;
		mb->un.varInitLnk.link_flags |= FLAGS_TOPOLOGY_FAILOVER;
		break;
	case FLAGS_LOCAL_LB:
		mb->un.varInitLnk.link_flags = FLAGS_LOCAL_LB;
		break;
	}

	if ((phba->pcidev->device == PCI_DEVICE_ID_LANCER_G6_FC ||
	     phba->pcidev->device == PCI_DEVICE_ID_LANCER_G7_FC) &&
	    mb->un.varInitLnk.link_flags & FLAGS_TOPOLOGY_MODE_LOOP) {
		mb->un.varInitLnk.link_flags = FLAGS_TOPOLOGY_MODE_PT_PT;
		phba->cfg_topology = FLAGS_TOPOLOGY_MODE_PT_PT;
	}

	/* Enable asynchronous ABTS responses from firmware */
	mb->un.varInitLnk.link_flags |= FLAGS_IMED_ABORT;

	/* NEW_FEATURE
	 * Setting up the link speed
	 */
	vpd = &phba->vpd;
	if (vpd->rev.feaLevelHigh >= 0x02){
		switch(linkspeed){
		case LPFC_USER_LINK_SPEED_1G:
			mb->un.varInitLnk.link_flags |= FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_1G;
			break;
		case LPFC_USER_LINK_SPEED_2G:
			mb->un.varInitLnk.link_flags |=	FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_2G;
			break;
		case LPFC_USER_LINK_SPEED_4G:
			mb->un.varInitLnk.link_flags |=	FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_4G;
			break;
		case LPFC_USER_LINK_SPEED_8G:
			mb->un.varInitLnk.link_flags |=	FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_8G;
			break;
		case LPFC_USER_LINK_SPEED_10G:
			mb->un.varInitLnk.link_flags |=	FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_10G;
			break;
		case LPFC_USER_LINK_SPEED_16G:
			mb->un.varInitLnk.link_flags |=	FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_16G;
			break;
		case LPFC_USER_LINK_SPEED_32G:
			mb->un.varInitLnk.link_flags |= FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_32G;
			break;
		case LPFC_USER_LINK_SPEED_64G:
			mb->un.varInitLnk.link_flags |= FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_64G;
			break;
		case LPFC_USER_LINK_SPEED_AUTO:
		default:
			mb->un.varInitLnk.link_speed = LINK_SPEED_AUTO;
			break;
		}

	}
	else
		mb->un.varInitLnk.link_speed = LINK_SPEED_AUTO;

	mb->mbxCommand = (volatile uint8_t)MBX_INIT_LINK;
	mb->mbxOwner = OWN_HOST;
	mb->un.varInitLnk.fabric_AL_PA = phba->fc_pref_ALPA;
	return;
}