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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct TYPE_4__ {int biuRev; } ;
struct TYPE_6__ {TYPE_1__ rev; } ;
struct lpfc_hba {TYPE_3__ vpd; } ;
struct TYPE_5__ {char* AttrString; } ;
struct lpfc_fdmi_attr_entry {TYPE_2__ un; } ;
struct lpfc_fdmi_attr_def {void* AttrType; void* AttrLen; int /*<<< orphan*/  AttrValue; } ;
typedef  TYPE_3__ lpfc_vpd_t ;

/* Variables and functions */
 int FOURBYTES ; 
 int RHBA_HARDWARE_VERSION ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memset (struct lpfc_fdmi_attr_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lpfc_fdmi_hba_attr_hdw_ver(struct lpfc_vport *vport,
			   struct lpfc_fdmi_attr_def *ad)
{
	struct lpfc_hba *phba = vport->phba;
	lpfc_vpd_t *vp = &phba->vpd;
	struct lpfc_fdmi_attr_entry *ae;
	uint32_t i, j, incr, size;

	ae = (struct lpfc_fdmi_attr_entry *)&ad->AttrValue;
	memset(ae, 0, 256);

	/* Convert JEDEC ID to ascii for hardware version */
	incr = vp->rev.biuRev;
	for (i = 0; i < 8; i++) {
		j = (incr & 0xf);
		if (j <= 9)
			ae->un.AttrString[7 - i] =
			    (char)((uint8_t) 0x30 +
				   (uint8_t) j);
		else
			ae->un.AttrString[7 - i] =
			    (char)((uint8_t) 0x61 +
				   (uint8_t) (j - 10));
		incr = (incr >> 4);
	}
	size = FOURBYTES + 8;
	ad->AttrLen = cpu_to_be16(size);
	ad->AttrType = cpu_to_be16(RHBA_HARDWARE_VERSION);
	return size;
}