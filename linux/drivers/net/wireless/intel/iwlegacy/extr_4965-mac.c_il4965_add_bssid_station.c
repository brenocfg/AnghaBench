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
typedef  size_t u8 ;
struct il_priv {int /*<<< orphan*/  sta_lock; TYPE_1__* stations; } ;
struct il_link_quality_cmd {int dummy; } ;
struct TYPE_2__ {struct il_link_quality_cmd* lq; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IL_ERR (char*,...) ; 
 size_t IL_INVALID_STATION ; 
 int /*<<< orphan*/  IL_STA_LOCAL ; 
 struct il_link_quality_cmd* il4965_sta_alloc_lq (struct il_priv*,size_t) ; 
 int il_add_station_common (struct il_priv*,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int il_send_lq_cmd (struct il_priv*,struct il_link_quality_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
il4965_add_bssid_station(struct il_priv *il, const u8 *addr, u8 *sta_id_r)
{
	int ret;
	u8 sta_id;
	struct il_link_quality_cmd *link_cmd;
	unsigned long flags;

	if (sta_id_r)
		*sta_id_r = IL_INVALID_STATION;

	ret = il_add_station_common(il, addr, 0, NULL, &sta_id);
	if (ret) {
		IL_ERR("Unable to add station %pM\n", addr);
		return ret;
	}

	if (sta_id_r)
		*sta_id_r = sta_id;

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].used |= IL_STA_LOCAL;
	spin_unlock_irqrestore(&il->sta_lock, flags);

	/* Set up default rate scaling table in device's station table */
	link_cmd = il4965_sta_alloc_lq(il, sta_id);
	if (!link_cmd) {
		IL_ERR("Unable to initialize rate scaling for station %pM.\n",
		       addr);
		return -ENOMEM;
	}

	ret = il_send_lq_cmd(il, link_cmd, CMD_SYNC, true);
	if (ret)
		IL_ERR("Link quality command failed (%d)\n", ret);

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].lq = link_cmd;
	spin_unlock_irqrestore(&il->sta_lock, flags);

	return 0;
}