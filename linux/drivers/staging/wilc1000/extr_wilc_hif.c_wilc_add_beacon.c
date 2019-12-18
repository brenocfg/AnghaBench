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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wid {int /*<<< orphan*/ * val; scalar_t__ size; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct cfg80211_beacon_data {scalar_t__ tail_len; int /*<<< orphan*/  tail; scalar_t__ head_len; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WID_ADD_BEACON ; 
 int /*<<< orphan*/  WID_BIN ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  put_unaligned_le32 (scalar_t__,int /*<<< orphan*/ *) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

int wilc_add_beacon(struct wilc_vif *vif, u32 interval, u32 dtim_period,
		    struct cfg80211_beacon_data *params)
{
	struct wid wid;
	int result;
	u8 *cur_byte;

	wid.id = WID_ADD_BEACON;
	wid.type = WID_BIN;
	wid.size = params->head_len + params->tail_len + 16;
	wid.val = kzalloc(wid.size, GFP_KERNEL);
	if (!wid.val)
		return -ENOMEM;

	cur_byte = wid.val;
	put_unaligned_le32(interval, cur_byte);
	cur_byte += 4;
	put_unaligned_le32(dtim_period, cur_byte);
	cur_byte += 4;
	put_unaligned_le32(params->head_len, cur_byte);
	cur_byte += 4;

	if (params->head_len > 0)
		memcpy(cur_byte, params->head, params->head_len);
	cur_byte += params->head_len;

	put_unaligned_le32(params->tail_len, cur_byte);
	cur_byte += 4;

	if (params->tail_len > 0)
		memcpy(cur_byte, params->tail, params->tail_len);

	result = wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
	if (result)
		netdev_err(vif->ndev, "Failed to send add beacon\n");

	kfree(wid.val);

	return result;
}