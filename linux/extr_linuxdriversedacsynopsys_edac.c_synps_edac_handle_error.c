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
struct synps_edac_priv {int /*<<< orphan*/  message; } ;
struct ecc_error_info {int row; int bank; int col; } ;
struct synps_ecc_status {scalar_t__ ue_cnt; struct ecc_error_info ueinfo; scalar_t__ ce_cnt; struct ecc_error_info ceinfo; } ;
struct mem_ctl_info {struct synps_edac_priv* pvt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 int /*<<< orphan*/  HW_EVENT_ERR_UNCORRECTED ; 
 int /*<<< orphan*/  SYNPS_EDAC_MSG_SIZE ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct synps_ecc_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int,int,int) ; 

__attribute__((used)) static void synps_edac_handle_error(struct mem_ctl_info *mci,
				    struct synps_ecc_status *p)
{
	struct synps_edac_priv *priv = mci->pvt_info;
	struct ecc_error_info *pinf;

	if (p->ce_cnt) {
		pinf = &p->ceinfo;
		snprintf(priv->message, SYNPS_EDAC_MSG_SIZE,
			 "DDR ECC error type :%s Row %d Bank %d Col %d ",
			 "CE", pinf->row, pinf->bank, pinf->col);
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci,
				     p->ce_cnt, 0, 0, 0, 0, 0, -1,
				     priv->message, "");
	}

	if (p->ue_cnt) {
		pinf = &p->ueinfo;
		snprintf(priv->message, SYNPS_EDAC_MSG_SIZE,
			 "DDR ECC error type :%s Row %d Bank %d Col %d ",
			 "UE", pinf->row, pinf->bank, pinf->col);
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci,
				     p->ue_cnt, 0, 0, 0, 0, 0, -1,
				     priv->message, "");
	}

	memset(p, 0, sizeof(*p));
}