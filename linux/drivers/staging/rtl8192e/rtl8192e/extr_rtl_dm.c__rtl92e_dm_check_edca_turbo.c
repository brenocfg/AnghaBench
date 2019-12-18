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
typedef  int /*<<< orphan*/  u8 ;
struct rt_hi_throughput {int IOTAction; size_t IOTPeer; } ;
struct TYPE_4__ {unsigned long txbytesunicast; unsigned long rxbytesunicast; } ;
struct r8192_priv {int bis_cur_rdlstate; int bcurrent_turbo_EDCA; TYPE_2__ stats; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ iw_mode; scalar_t__ state; int bis_any_nonbepkts; scalar_t__ mode; int /*<<< orphan*/  (* SetHwRegHandler ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;struct rt_hi_throughput* pHTInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC0_BE ; 
 int /*<<< orphan*/  EDCAPARA_BE ; 
 int HT_IOT_ACT_DISABLE_EDCA_TURBO ; 
 int HT_IOT_ACT_EDCA_BIAS_ON_RX ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ RTLLIB_LINKED ; 
 scalar_t__ WIRELESS_MODE_G ; 
 int /*<<< orphan*/ * edca_setting_DL ; 
 int /*<<< orphan*/ * edca_setting_DL_GMode ; 
 int /*<<< orphan*/ * edca_setting_UL ; 
 int /*<<< orphan*/  rtl92e_writel (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _rtl92e_dm_check_edca_turbo(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	struct rt_hi_throughput *pHTInfo = priv->rtllib->pHTInfo;

	static unsigned long lastTxOkCnt;
	static unsigned long lastRxOkCnt;
	unsigned long curTxOkCnt = 0;
	unsigned long curRxOkCnt = 0;

	if (priv->rtllib->iw_mode == IW_MODE_ADHOC)
		goto dm_CheckEdcaTurbo_EXIT;
	if (priv->rtllib->state != RTLLIB_LINKED)
		goto dm_CheckEdcaTurbo_EXIT;
	if (priv->rtllib->pHTInfo->IOTAction & HT_IOT_ACT_DISABLE_EDCA_TURBO)
		goto dm_CheckEdcaTurbo_EXIT;

	if (!priv->rtllib->bis_any_nonbepkts) {
		curTxOkCnt = priv->stats.txbytesunicast - lastTxOkCnt;
		curRxOkCnt = priv->stats.rxbytesunicast - lastRxOkCnt;
		if (pHTInfo->IOTAction & HT_IOT_ACT_EDCA_BIAS_ON_RX) {
			if (curTxOkCnt > 4*curRxOkCnt) {
				if (priv->bis_cur_rdlstate ||
				    !priv->bcurrent_turbo_EDCA) {
					rtl92e_writel(dev, EDCAPARA_BE,
						      edca_setting_UL[pHTInfo->IOTPeer]);
					priv->bis_cur_rdlstate = false;
				}
			} else {
				if (!priv->bis_cur_rdlstate ||
				    !priv->bcurrent_turbo_EDCA) {
					if (priv->rtllib->mode == WIRELESS_MODE_G)
						rtl92e_writel(dev, EDCAPARA_BE,
							      edca_setting_DL_GMode[pHTInfo->IOTPeer]);
					else
						rtl92e_writel(dev, EDCAPARA_BE,
							      edca_setting_DL[pHTInfo->IOTPeer]);
					priv->bis_cur_rdlstate = true;
				}
			}
			priv->bcurrent_turbo_EDCA = true;
		} else {
			if (curRxOkCnt > 4*curTxOkCnt) {
				if (!priv->bis_cur_rdlstate ||
				    !priv->bcurrent_turbo_EDCA) {
					if (priv->rtllib->mode == WIRELESS_MODE_G)
						rtl92e_writel(dev, EDCAPARA_BE,
							      edca_setting_DL_GMode[pHTInfo->IOTPeer]);
					else
						rtl92e_writel(dev, EDCAPARA_BE,
							      edca_setting_DL[pHTInfo->IOTPeer]);
					priv->bis_cur_rdlstate = true;
				}
			} else {
				if (priv->bis_cur_rdlstate ||
				    !priv->bcurrent_turbo_EDCA) {
					rtl92e_writel(dev, EDCAPARA_BE,
						      edca_setting_UL[pHTInfo->IOTPeer]);
					priv->bis_cur_rdlstate = false;
				}

			}

			priv->bcurrent_turbo_EDCA = true;
		}
	} else {
		 if (priv->bcurrent_turbo_EDCA) {
			u8 tmp = AC0_BE;

			priv->rtllib->SetHwRegHandler(dev, HW_VAR_AC_PARAM,
						      (u8 *)(&tmp));
			priv->bcurrent_turbo_EDCA = false;
		}
	}


dm_CheckEdcaTurbo_EXIT:
	priv->rtllib->bis_any_nonbepkts = false;
	lastTxOkCnt = priv->stats.txbytesunicast;
	lastRxOkCnt = priv->stats.rxbytesunicast;
}