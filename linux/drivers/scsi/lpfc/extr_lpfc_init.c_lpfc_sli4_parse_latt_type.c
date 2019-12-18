#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct lpfc_hba {int dummy; } ;
struct lpfc_acqe_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
#define  LPFC_ASYNC_LINK_STATUS_DOWN 131 
#define  LPFC_ASYNC_LINK_STATUS_LOGICAL_DOWN 130 
#define  LPFC_ASYNC_LINK_STATUS_LOGICAL_UP 129 
#define  LPFC_ASYNC_LINK_STATUS_UP 128 
 int /*<<< orphan*/  LPFC_ATT_LINK_DOWN ; 
 int /*<<< orphan*/  LPFC_ATT_LINK_UP ; 
 int /*<<< orphan*/  LPFC_ATT_RESERVED ; 
 int bf_get (int /*<<< orphan*/ ,struct lpfc_acqe_link*) ; 
 int /*<<< orphan*/  lpfc_acqe_link_status ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static uint8_t
lpfc_sli4_parse_latt_type(struct lpfc_hba *phba,
			  struct lpfc_acqe_link *acqe_link)
{
	uint8_t att_type;

	switch (bf_get(lpfc_acqe_link_status, acqe_link)) {
	case LPFC_ASYNC_LINK_STATUS_DOWN:
	case LPFC_ASYNC_LINK_STATUS_LOGICAL_DOWN:
		att_type = LPFC_ATT_LINK_DOWN;
		break;
	case LPFC_ASYNC_LINK_STATUS_UP:
		/* Ignore physical link up events - wait for logical link up */
		att_type = LPFC_ATT_RESERVED;
		break;
	case LPFC_ASYNC_LINK_STATUS_LOGICAL_UP:
		att_type = LPFC_ATT_LINK_UP;
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0399 Invalid link attention type: x%x\n",
				bf_get(lpfc_acqe_link_status, acqe_link));
		att_type = LPFC_ATT_RESERVED;
		break;
	}
	return att_type;
}