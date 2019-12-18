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
typedef  int /*<<< orphan*/  u16 ;
struct rt_dot11d_info {int* channel_map; int* max_tx_pwr_dbm_list; int /*<<< orphan*/  state; int /*<<< orphan*/  country_ie_buf; int /*<<< orphan*/  country_ie_len; } ;
struct ieee80211_device {int /*<<< orphan*/  dev; } ;
struct chnl_txpower_triple {size_t first_channel; int num_channels; int max_tx_pwr_dbm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11D_STATE_LEARNED ; 
 struct rt_dot11d_info* GET_DOT11D_INFO (struct ieee80211_device*) ; 
 int MAX_CHANNEL_NUMBER ; 
 int /*<<< orphan*/  UPDATE_CIE_SRC (struct ieee80211_device*,size_t*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 

void dot11d_update_country_ie(struct ieee80211_device *dev, u8 *pTaddr,
			    u16 CoutryIeLen, u8 *pCoutryIe)
{
	struct rt_dot11d_info *dot11d_info = GET_DOT11D_INFO(dev);
	u8 i, j, NumTriples, MaxChnlNum;
	struct chnl_txpower_triple *pTriple;

	memset(dot11d_info->channel_map, 0, MAX_CHANNEL_NUMBER + 1);
	memset(dot11d_info->max_tx_pwr_dbm_list, 0xFF, MAX_CHANNEL_NUMBER + 1);
	MaxChnlNum = 0;
	NumTriples = (CoutryIeLen - 3) / 3; /* skip 3-byte country string. */
	pTriple = (struct chnl_txpower_triple *)(pCoutryIe + 3);
	for (i = 0; i < NumTriples; i++) {
		if (MaxChnlNum >= pTriple->first_channel) {
			/* It is not in a monotonically increasing order, so
			 * stop processing.
			 */
			netdev_err(dev->dev, "dot11d_update_country_ie(): Invalid country IE, skip it........1\n");
			return;
		}
		if (MAX_CHANNEL_NUMBER < (pTriple->first_channel + pTriple->num_channels)) {
			/* It is not a valid set of channel id, so stop
			 * processing.
			 */
			netdev_err(dev->dev, "dot11d_update_country_ie(): Invalid country IE, skip it........2\n");
			return;
		}

		for (j = 0; j < pTriple->num_channels; j++) {
			dot11d_info->channel_map[pTriple->first_channel + j] = 1;
			dot11d_info->max_tx_pwr_dbm_list[pTriple->first_channel + j] = pTriple->max_tx_pwr_dbm;
			MaxChnlNum = pTriple->first_channel + j;
		}

		pTriple = (struct chnl_txpower_triple *)((u8 *)pTriple + 3);
	}
	netdev_info(dev->dev, "Channel List:");
	for (i = 1; i <= MAX_CHANNEL_NUMBER; i++)
		if (dot11d_info->channel_map[i] > 0)
			netdev_info(dev->dev, " %d", i);
	netdev_info(dev->dev, "\n");

	UPDATE_CIE_SRC(dev, pTaddr);

	dot11d_info->country_ie_len = CoutryIeLen;
	memcpy(dot11d_info->country_ie_buf, pCoutryIe, CoutryIeLen);
	dot11d_info->state = DOT11D_STATE_LEARNED;
}