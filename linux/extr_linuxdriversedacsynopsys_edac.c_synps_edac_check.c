#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ue_cnt; scalar_t__ ce_cnt; } ;
struct synps_edac_priv {int /*<<< orphan*/  ue_cnt; int /*<<< orphan*/  ce_cnt; TYPE_1__ stat; int /*<<< orphan*/  baseaddr; } ;
struct mem_ctl_info {struct synps_edac_priv* pvt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int synps_edac_geterror_info (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  synps_edac_handle_error (struct mem_ctl_info*,TYPE_1__*) ; 

__attribute__((used)) static void synps_edac_check(struct mem_ctl_info *mci)
{
	struct synps_edac_priv *priv = mci->pvt_info;
	int status;

	status = synps_edac_geterror_info(priv->baseaddr, &priv->stat);
	if (status)
		return;

	priv->ce_cnt += priv->stat.ce_cnt;
	priv->ue_cnt += priv->stat.ue_cnt;
	synps_edac_handle_error(mci, &priv->stat);

	edac_dbg(3, "Total error count ce %d ue %d\n",
		 priv->ce_cnt, priv->ue_cnt);
}