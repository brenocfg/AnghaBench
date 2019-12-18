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
struct lpfc_hba {int hba_flag; int fc_linkspeed; } ;
struct TYPE_2__ {void* AttrInt; } ;
struct lpfc_fdmi_attr_entry {TYPE_1__ un; } ;
struct lpfc_fdmi_attr_def {void* AttrType; void* AttrLen; int /*<<< orphan*/  AttrValue; } ;

/* Variables and functions */
 int FOURBYTES ; 
 int HBA_FCOE_MODE ; 
 void* HBA_PORTSPEED_100GE ; 
 void* HBA_PORTSPEED_10GE ; 
 void* HBA_PORTSPEED_10GFC ; 
 void* HBA_PORTSPEED_128GFC ; 
 void* HBA_PORTSPEED_16GFC ; 
 void* HBA_PORTSPEED_1GFC ; 
 void* HBA_PORTSPEED_25GE ; 
 void* HBA_PORTSPEED_2GFC ; 
 void* HBA_PORTSPEED_32GFC ; 
 void* HBA_PORTSPEED_40GE ; 
 void* HBA_PORTSPEED_4GFC ; 
 void* HBA_PORTSPEED_64GFC ; 
 void* HBA_PORTSPEED_8GFC ; 
 void* HBA_PORTSPEED_UNKNOWN ; 
#define  LPFC_ASYNC_LINK_SPEED_100GBPS 140 
#define  LPFC_ASYNC_LINK_SPEED_10GBPS 139 
#define  LPFC_ASYNC_LINK_SPEED_25GBPS 138 
#define  LPFC_ASYNC_LINK_SPEED_40GBPS 137 
#define  LPFC_LINK_SPEED_10GHZ 136 
#define  LPFC_LINK_SPEED_128GHZ 135 
#define  LPFC_LINK_SPEED_16GHZ 134 
#define  LPFC_LINK_SPEED_1GHZ 133 
#define  LPFC_LINK_SPEED_2GHZ 132 
#define  LPFC_LINK_SPEED_32GHZ 131 
#define  LPFC_LINK_SPEED_4GHZ 130 
#define  LPFC_LINK_SPEED_64GHZ 129 
#define  LPFC_LINK_SPEED_8GHZ 128 
 int RPRT_PORT_SPEED ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (void*) ; 

__attribute__((used)) static int
lpfc_fdmi_port_attr_speed(struct lpfc_vport *vport,
			  struct lpfc_fdmi_attr_def *ad)
{
	struct lpfc_hba   *phba = vport->phba;
	struct lpfc_fdmi_attr_entry *ae;
	uint32_t size;

	ae = (struct lpfc_fdmi_attr_entry *)&ad->AttrValue;

	if (!(phba->hba_flag & HBA_FCOE_MODE)) {
		switch (phba->fc_linkspeed) {
		case LPFC_LINK_SPEED_1GHZ:
			ae->un.AttrInt = HBA_PORTSPEED_1GFC;
			break;
		case LPFC_LINK_SPEED_2GHZ:
			ae->un.AttrInt = HBA_PORTSPEED_2GFC;
			break;
		case LPFC_LINK_SPEED_4GHZ:
			ae->un.AttrInt = HBA_PORTSPEED_4GFC;
			break;
		case LPFC_LINK_SPEED_8GHZ:
			ae->un.AttrInt = HBA_PORTSPEED_8GFC;
			break;
		case LPFC_LINK_SPEED_10GHZ:
			ae->un.AttrInt = HBA_PORTSPEED_10GFC;
			break;
		case LPFC_LINK_SPEED_16GHZ:
			ae->un.AttrInt = HBA_PORTSPEED_16GFC;
			break;
		case LPFC_LINK_SPEED_32GHZ:
			ae->un.AttrInt = HBA_PORTSPEED_32GFC;
			break;
		case LPFC_LINK_SPEED_64GHZ:
			ae->un.AttrInt = HBA_PORTSPEED_64GFC;
			break;
		case LPFC_LINK_SPEED_128GHZ:
			ae->un.AttrInt = HBA_PORTSPEED_128GFC;
			break;
		default:
			ae->un.AttrInt = HBA_PORTSPEED_UNKNOWN;
			break;
		}
	} else {
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
		default:
			ae->un.AttrInt = HBA_PORTSPEED_UNKNOWN;
			break;
		}
	}

	ae->un.AttrInt = cpu_to_be32(ae->un.AttrInt);
	size = FOURBYTES + sizeof(uint32_t);
	ad->AttrLen = cpu_to_be16(size);
	ad->AttrType = cpu_to_be16(RPRT_PORT_SPEED);
	return size;
}