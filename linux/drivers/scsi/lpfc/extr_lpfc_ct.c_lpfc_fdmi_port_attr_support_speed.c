#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int hba_flag; int lmt; int fc_linkspeed; } ;
struct TYPE_2__ {int /*<<< orphan*/  AttrInt; } ;
struct lpfc_fdmi_attr_entry {TYPE_1__ un; } ;
struct lpfc_fdmi_attr_def {void* AttrType; void* AttrLen; int /*<<< orphan*/  AttrValue; } ;

/* Variables and functions */
 int FOURBYTES ; 
 int HBA_FCOE_MODE ; 
 int /*<<< orphan*/  HBA_PORTSPEED_100GE ; 
 int /*<<< orphan*/  HBA_PORTSPEED_10GE ; 
 int /*<<< orphan*/  HBA_PORTSPEED_10GFC ; 
 int /*<<< orphan*/  HBA_PORTSPEED_128GFC ; 
 int /*<<< orphan*/  HBA_PORTSPEED_16GFC ; 
 int /*<<< orphan*/  HBA_PORTSPEED_1GFC ; 
 int /*<<< orphan*/  HBA_PORTSPEED_25GE ; 
 int /*<<< orphan*/  HBA_PORTSPEED_2GFC ; 
 int /*<<< orphan*/  HBA_PORTSPEED_32GFC ; 
 int /*<<< orphan*/  HBA_PORTSPEED_40GE ; 
 int /*<<< orphan*/  HBA_PORTSPEED_4GFC ; 
 int /*<<< orphan*/  HBA_PORTSPEED_64GFC ; 
 int /*<<< orphan*/  HBA_PORTSPEED_8GFC ; 
 int LMT_10Gb ; 
 int LMT_128Gb ; 
 int LMT_16Gb ; 
 int LMT_1Gb ; 
 int LMT_2Gb ; 
 int LMT_32Gb ; 
 int LMT_4Gb ; 
 int LMT_64Gb ; 
 int LMT_8Gb ; 
#define  LPFC_ASYNC_LINK_SPEED_100GBPS 131 
#define  LPFC_ASYNC_LINK_SPEED_10GBPS 130 
#define  LPFC_ASYNC_LINK_SPEED_25GBPS 129 
#define  LPFC_ASYNC_LINK_SPEED_40GBPS 128 
 int RPRT_SUPPORTED_SPEED ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_fdmi_port_attr_support_speed(struct lpfc_vport *vport,
				  struct lpfc_fdmi_attr_def *ad)
{
	struct lpfc_hba   *phba = vport->phba;
	struct lpfc_fdmi_attr_entry *ae;
	uint32_t size;

	ae = (struct lpfc_fdmi_attr_entry *)&ad->AttrValue;

	ae->un.AttrInt = 0;
	if (!(phba->hba_flag & HBA_FCOE_MODE)) {
		if (phba->lmt & LMT_128Gb)
			ae->un.AttrInt |= HBA_PORTSPEED_128GFC;
		if (phba->lmt & LMT_64Gb)
			ae->un.AttrInt |= HBA_PORTSPEED_64GFC;
		if (phba->lmt & LMT_32Gb)
			ae->un.AttrInt |= HBA_PORTSPEED_32GFC;
		if (phba->lmt & LMT_16Gb)
			ae->un.AttrInt |= HBA_PORTSPEED_16GFC;
		if (phba->lmt & LMT_10Gb)
			ae->un.AttrInt |= HBA_PORTSPEED_10GFC;
		if (phba->lmt & LMT_8Gb)
			ae->un.AttrInt |= HBA_PORTSPEED_8GFC;
		if (phba->lmt & LMT_4Gb)
			ae->un.AttrInt |= HBA_PORTSPEED_4GFC;
		if (phba->lmt & LMT_2Gb)
			ae->un.AttrInt |= HBA_PORTSPEED_2GFC;
		if (phba->lmt & LMT_1Gb)
			ae->un.AttrInt |= HBA_PORTSPEED_1GFC;
	} else {
		/* FCoE links support only one speed */
		switch (phba->fc_linkspeed) {
		case LPFC_ASYNC_LINK_SPEED_10GBPS:
			ae->un.AttrInt = HBA_PORTSPEED_10GE;
			break;
		case LPFC_ASYNC_LINK_SPEED_25GBPS:
			ae->un.AttrInt = HBA_PORTSPEED_25GE;
			break;
		case LPFC_ASYNC_LINK_SPEED_40GBPS:
			ae->un.AttrInt = HBA_PORTSPEED_40GE;
			break;
		case LPFC_ASYNC_LINK_SPEED_100GBPS:
			ae->un.AttrInt = HBA_PORTSPEED_100GE;
			break;
		}
	}
	ae->un.AttrInt = cpu_to_be32(ae->un.AttrInt);
	size = FOURBYTES + sizeof(uint32_t);
	ad->AttrLen = cpu_to_be16(size);
	ad->AttrType = cpu_to_be16(RPRT_SUPPORTED_SPEED);
	return size;
}