#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ bbRcvSizeLsb; scalar_t__ bbRcvSizeMsb; } ;
struct serv_parm {TYPE_1__ cmn; } ;
struct lpfc_vport {int /*<<< orphan*/  fc_sparam; } ;
struct TYPE_4__ {int AttrInt; } ;
struct lpfc_fdmi_attr_entry {TYPE_2__ un; } ;
struct lpfc_fdmi_attr_def {void* AttrType; void* AttrLen; int /*<<< orphan*/  AttrValue; } ;

/* Variables and functions */
 int FOURBYTES ; 
 int RPRT_MAX_FRAME_SIZE ; 
 void* cpu_to_be16 (int) ; 
 int cpu_to_be32 (int) ; 

__attribute__((used)) static int
lpfc_fdmi_port_attr_max_frame(struct lpfc_vport *vport,
			      struct lpfc_fdmi_attr_def *ad)
{
	struct serv_parm *hsp;
	struct lpfc_fdmi_attr_entry *ae;
	uint32_t size;

	ae = (struct lpfc_fdmi_attr_entry *)&ad->AttrValue;

	hsp = (struct serv_parm *)&vport->fc_sparam;
	ae->un.AttrInt = (((uint32_t) hsp->cmn.bbRcvSizeMsb & 0x0F) << 8) |
			  (uint32_t) hsp->cmn.bbRcvSizeLsb;
	ae->un.AttrInt = cpu_to_be32(ae->un.AttrInt);
	size = FOURBYTES + sizeof(uint32_t);
	ad->AttrLen = cpu_to_be16(size);
	ad->AttrType = cpu_to_be16(RPRT_MAX_FRAME_SIZE);
	return size;
}