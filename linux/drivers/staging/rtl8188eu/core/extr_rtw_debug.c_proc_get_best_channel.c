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
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct mlme_ext_priv {TYPE_1__* channel_set; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int ChannelNum; scalar_t__ rx_count; } ;

/* Variables and functions */
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 scalar_t__ snprintf (char*,int,char*,size_t,...) ; 

int proc_get_best_channel(char *page, char **start,
			  off_t offset, int count,
			  int *eof, void *data)
{
	struct net_device *dev = data;
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(dev);
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	int len = 0;
	u32 i, best_channel_24G = 1, index_24G = 0;

	for (i = 0; pmlmeext->channel_set[i].ChannelNum != 0; i++) {
		if (pmlmeext->channel_set[i].ChannelNum == 1)
			index_24G = i;
	}

	for (i = 0; pmlmeext->channel_set[i].ChannelNum != 0; i++) {
		/*  2.4G */
		if (pmlmeext->channel_set[i].ChannelNum == 6) {
			if (pmlmeext->channel_set[i].rx_count < pmlmeext->channel_set[index_24G].rx_count) {
				index_24G = i;
				best_channel_24G = pmlmeext->channel_set[i].ChannelNum;
			}
		}

		/*  debug */
		len += snprintf(page + len, count - len, "The rx cnt of channel %3d = %d\n",
					pmlmeext->channel_set[i].ChannelNum, pmlmeext->channel_set[i].rx_count);
	}

	len += snprintf(page + len, count - len, "best_channel_24G = %d\n", best_channel_24G);

	*eof = 1;
	return len;
}