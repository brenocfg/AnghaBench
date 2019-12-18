#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_12__ {scalar_t__* wwn; } ;
struct TYPE_15__ {TYPE_3__ u; } ;
struct TYPE_11__ {int /*<<< orphan*/ * vendorVersion; } ;
struct TYPE_10__ {int valid_vendor_ver_level; } ;
struct TYPE_14__ {TYPE_6__ portName; TYPE_6__ nodeName; TYPE_2__ un; TYPE_1__ cmn; } ;
struct lpfc_vport {int vport_flag; TYPE_6__ fc_portname; TYPE_5__ fc_sparam; TYPE_4__* phba; TYPE_6__ fc_nodename; } ;
struct lpfc_name {int dummy; } ;
struct TYPE_13__ {scalar_t__ cfg_soft_wwpn; scalar_t__ cfg_soft_wwnn; } ;

/* Variables and functions */
 scalar_t__ FAPWWN_KEY_VENDOR ; 
 int FAWWPN_PARAM_CHG ; 
 int FAWWPN_SET ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (TYPE_6__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  u64_to_wwn (scalar_t__,scalar_t__*) ; 

void
lpfc_update_vport_wwn(struct lpfc_vport *vport)
{
	uint8_t vvvl = vport->fc_sparam.cmn.valid_vendor_ver_level;
	u32 *fawwpn_key = (u32 *)&vport->fc_sparam.un.vendorVersion[0];

	/* If the soft name exists then update it using the service params */
	if (vport->phba->cfg_soft_wwnn)
		u64_to_wwn(vport->phba->cfg_soft_wwnn,
			   vport->fc_sparam.nodeName.u.wwn);
	if (vport->phba->cfg_soft_wwpn)
		u64_to_wwn(vport->phba->cfg_soft_wwpn,
			   vport->fc_sparam.portName.u.wwn);

	/*
	 * If the name is empty or there exists a soft name
	 * then copy the service params name, otherwise use the fc name
	 */
	if (vport->fc_nodename.u.wwn[0] == 0 || vport->phba->cfg_soft_wwnn)
		memcpy(&vport->fc_nodename, &vport->fc_sparam.nodeName,
			sizeof(struct lpfc_name));
	else
		memcpy(&vport->fc_sparam.nodeName, &vport->fc_nodename,
			sizeof(struct lpfc_name));

	/*
	 * If the port name has changed, then set the Param changes flag
	 * to unreg the login
	 */
	if (vport->fc_portname.u.wwn[0] != 0 &&
		memcmp(&vport->fc_portname, &vport->fc_sparam.portName,
			sizeof(struct lpfc_name)))
		vport->vport_flag |= FAWWPN_PARAM_CHG;

	if (vport->fc_portname.u.wwn[0] == 0 ||
	    vport->phba->cfg_soft_wwpn ||
	    (vvvl == 1 && cpu_to_be32(*fawwpn_key) == FAPWWN_KEY_VENDOR) ||
	    vport->vport_flag & FAWWPN_SET) {
		memcpy(&vport->fc_portname, &vport->fc_sparam.portName,
			sizeof(struct lpfc_name));
		vport->vport_flag &= ~FAWWPN_SET;
		if (vvvl == 1 && cpu_to_be32(*fawwpn_key) == FAPWWN_KEY_VENDOR)
			vport->vport_flag |= FAWWPN_SET;
	}
	else
		memcpy(&vport->fc_sparam.portName, &vport->fc_portname,
			sizeof(struct lpfc_name));
}