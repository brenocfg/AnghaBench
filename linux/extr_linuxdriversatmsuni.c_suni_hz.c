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
struct timer_list {int dummy; } ;
struct k_sonet_stats {int dummy; } ;
struct suni_priv {struct k_sonet_stats sonet_stats; struct atm_dev* dev; struct suni_priv* next; } ;
struct atm_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_LIMITED (int /*<<< orphan*/ ,int) ; 
 int GET (int /*<<< orphan*/ ) ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  MRI ; 
 int /*<<< orphan*/  PUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RACP_CHEC ; 
 int /*<<< orphan*/  RACP_RCC ; 
 int /*<<< orphan*/  RACP_RCCL ; 
 int /*<<< orphan*/  RACP_RCCM ; 
 int /*<<< orphan*/  RACP_UHEC ; 
 int /*<<< orphan*/  RLOP_LB ; 
 int /*<<< orphan*/  RLOP_LBL ; 
 int /*<<< orphan*/  RLOP_LBM ; 
 int /*<<< orphan*/  RLOP_LF ; 
 int /*<<< orphan*/  RLOP_LFL ; 
 int /*<<< orphan*/  RLOP_LFM ; 
 int /*<<< orphan*/  RPOP_PBL ; 
 int /*<<< orphan*/  RPOP_PBM ; 
 int /*<<< orphan*/  RPOP_PFL ; 
 int /*<<< orphan*/  RPOP_PFM ; 
 int /*<<< orphan*/  RSOP_SBL ; 
 int /*<<< orphan*/  RSOP_SBM ; 
 int /*<<< orphan*/  TACP_TCC ; 
 int /*<<< orphan*/  TACP_TCCL ; 
 int /*<<< orphan*/  TACP_TCCM ; 
 int /*<<< orphan*/  corr_hcs ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  line_bip ; 
 int /*<<< orphan*/  line_febe ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  path_bip ; 
 int /*<<< orphan*/  path_febe ; 
 int /*<<< orphan*/  poll_timer ; 
 int /*<<< orphan*/  rx_cells ; 
 int /*<<< orphan*/  section_bip ; 
 struct suni_priv* sunis ; 
 int /*<<< orphan*/  tx_cells ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  uncorr_hcs ; 

__attribute__((used)) static void suni_hz(struct timer_list *timer)
{
	struct suni_priv *walk;
	struct atm_dev *dev;
	struct k_sonet_stats *stats;

	for (walk = sunis; walk; walk = walk->next) {
		dev = walk->dev;
		stats = &walk->sonet_stats;
		PUT(0,MRI); /* latch counters */
		udelay(1);
		ADD_LIMITED(section_bip,(GET(RSOP_SBL) & 0xff) |
		    ((GET(RSOP_SBM) & 0xff) << 8));
		ADD_LIMITED(line_bip,(GET(RLOP_LBL) & 0xff) |
		    ((GET(RLOP_LB) & 0xff) << 8) |
		    ((GET(RLOP_LBM) & 0xf) << 16));
		ADD_LIMITED(path_bip,(GET(RPOP_PBL) & 0xff) |
		    ((GET(RPOP_PBM) & 0xff) << 8));
		ADD_LIMITED(line_febe,(GET(RLOP_LFL) & 0xff) |
		    ((GET(RLOP_LF) & 0xff) << 8) |
		    ((GET(RLOP_LFM) & 0xf) << 16));
		ADD_LIMITED(path_febe,(GET(RPOP_PFL) & 0xff) |
		    ((GET(RPOP_PFM) & 0xff) << 8));
		ADD_LIMITED(corr_hcs,GET(RACP_CHEC) & 0xff);
		ADD_LIMITED(uncorr_hcs,GET(RACP_UHEC) & 0xff);
		ADD_LIMITED(rx_cells,(GET(RACP_RCCL) & 0xff) |
		    ((GET(RACP_RCC) & 0xff) << 8) |
		    ((GET(RACP_RCCM) & 7) << 16));
		ADD_LIMITED(tx_cells,(GET(TACP_TCCL) & 0xff) |
		    ((GET(TACP_TCC) & 0xff) << 8) |
		    ((GET(TACP_TCCM) & 7) << 16));
	}
	if (timer) mod_timer(&poll_timer,jiffies+HZ);
}