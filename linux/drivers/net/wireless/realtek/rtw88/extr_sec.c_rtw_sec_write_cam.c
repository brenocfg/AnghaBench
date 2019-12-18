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
typedef  size_t u8 ;
typedef  int u32 ;
struct rtw_sec_desc {int /*<<< orphan*/  cam_map; struct rtw_cam_entry* cam_table; } ;
struct rtw_dev {int dummy; } ;
struct rtw_cam_entry {int valid; int group; size_t hw_key_type; int* addr; struct ieee80211_key_conf* key; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct ieee80211_key_conf {int flags; int keyidx; int* key; } ;

/* Variables and functions */
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 size_t RTW_SEC_CAM_ENTRY_SHIFT ; 
 int RTW_SEC_CMD_POLLING ; 
 int /*<<< orphan*/  RTW_SEC_CMD_REG ; 
 int RTW_SEC_CMD_WRITE_ENABLE ; 
 int /*<<< orphan*/  RTW_SEC_WRITE_REG ; 
 int /*<<< orphan*/  eth_broadcast_addr (int*) ; 
 int /*<<< orphan*/  ether_addr_copy (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 

void rtw_sec_write_cam(struct rtw_dev *rtwdev,
		       struct rtw_sec_desc *sec,
		       struct ieee80211_sta *sta,
		       struct ieee80211_key_conf *key,
		       u8 hw_key_type, u8 hw_key_idx)
{
	struct rtw_cam_entry *cam = &sec->cam_table[hw_key_idx];
	u32 write_cmd;
	u32 command;
	u32 content;
	u32 addr;
	int i, j;

	set_bit(hw_key_idx, sec->cam_map);
	cam->valid = true;
	cam->group = !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE);
	cam->hw_key_type = hw_key_type;
	cam->key = key;
	if (sta)
		ether_addr_copy(cam->addr, sta->addr);
	else
		eth_broadcast_addr(cam->addr);

	write_cmd = RTW_SEC_CMD_WRITE_ENABLE | RTW_SEC_CMD_POLLING;
	addr = hw_key_idx << RTW_SEC_CAM_ENTRY_SHIFT;
	for (i = 5; i >= 0; i--) {
		switch (i) {
		case 0:
			content = ((key->keyidx & 0x3))		|
				  ((hw_key_type & 0x7)	<< 2)	|
				  (cam->group		<< 6)	|
				  (cam->valid		<< 15)	|
				  (cam->addr[0]		<< 16)	|
				  (cam->addr[1]		<< 24);
			break;
		case 1:
			content = (cam->addr[2])		|
				  (cam->addr[3]		<< 8)	|
				  (cam->addr[4]		<< 16)	|
				  (cam->addr[5]		<< 24);
			break;
		default:
			j = (i - 2) << 2;
			content = (key->key[j])			|
				  (key->key[j + 1]	<< 8)	|
				  (key->key[j + 2]	<< 16)	|
				  (key->key[j + 3]	<< 24);
			break;
		}

		command = write_cmd | (addr + i);
		rtw_write32(rtwdev, RTW_SEC_WRITE_REG, content);
		rtw_write32(rtwdev, RTW_SEC_CMD_REG, command);
	}
}