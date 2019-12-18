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
struct TYPE_2__ {int rx_ampdu_min_spacing; int /*<<< orphan*/  ch_offset; int /*<<< orphan*/  ht_option; } ;
struct sta_info {scalar_t__ bw_mode; scalar_t__ pid; scalar_t__ isrc; TYPE_1__ htpriv; int /*<<< orphan*/  stbc; int /*<<< orphan*/  ldpc; int /*<<< orphan*/  raid; int /*<<< orphan*/  qos_option; int /*<<< orphan*/  cts2self; int /*<<< orphan*/  rtsen; } ;
struct pkt_attrib {int ampdu_spacing; scalar_t__ bwmode; int ampdu_en; int retry_ctrl; int pctrl; int /*<<< orphan*/  ch_offset; int /*<<< orphan*/  ht_en; int /*<<< orphan*/  stbc; int /*<<< orphan*/  ldpc; int /*<<< orphan*/  sgi; int /*<<< orphan*/  raid; int /*<<< orphan*/  qos_en; scalar_t__ triggered; scalar_t__ eosp; scalar_t__ mdata; int /*<<< orphan*/  cts2self; int /*<<< orphan*/  rtsen; } ;
struct mlme_ext_priv {scalar_t__ cur_bwmode; } ;
struct adapter {int driver_ampdu_spacing; struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  query_ra_short_GI (struct sta_info*) ; 

__attribute__((used)) static void update_attrib_phy_info(struct adapter *padapter, struct pkt_attrib *pattrib, struct sta_info *psta)
{
	struct mlme_ext_priv *mlmeext = &padapter->mlmeextpriv;

	pattrib->rtsen = psta->rtsen;
	pattrib->cts2self = psta->cts2self;

	pattrib->mdata = 0;
	pattrib->eosp = 0;
	pattrib->triggered = 0;
	pattrib->ampdu_spacing = 0;

	/* qos_en, ht_en, init rate, , bw, ch_offset, sgi */
	pattrib->qos_en = psta->qos_option;

	pattrib->raid = psta->raid;

	if (mlmeext->cur_bwmode < psta->bw_mode)
		pattrib->bwmode = mlmeext->cur_bwmode;
	else
		pattrib->bwmode = psta->bw_mode;

	pattrib->sgi = query_ra_short_GI(psta);

	pattrib->ldpc = psta->ldpc;
	pattrib->stbc = psta->stbc;

	pattrib->ht_en = psta->htpriv.ht_option;
	pattrib->ch_offset = psta->htpriv.ch_offset;
	pattrib->ampdu_en = false;

	if (padapter->driver_ampdu_spacing != 0xFF) /* driver control AMPDU Density for peer sta's rx */
		pattrib->ampdu_spacing = padapter->driver_ampdu_spacing;
	else
		pattrib->ampdu_spacing = psta->htpriv.rx_ampdu_min_spacing;

	/* if (pattrib->ht_en && psta->htpriv.ampdu_enable) */
	/*  */
	/* 	if (psta->htpriv.agg_enable_bitmap & BIT(pattrib->priority)) */
	/* 		pattrib->ampdu_en = true; */
	/*  */


	pattrib->retry_ctrl = false;

#ifdef CONFIG_AUTO_AP_MODE
	if (psta->isrc && psta->pid > 0)
		pattrib->pctrl = true;
#endif

}