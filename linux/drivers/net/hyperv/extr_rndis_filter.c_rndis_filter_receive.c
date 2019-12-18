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
typedef  int /*<<< orphan*/  u32 ;
struct rndis_message {int ndis_msg_type; int /*<<< orphan*/  msg_len; } ;
struct netvsc_device {int dummy; } ;
struct netvsc_channel {int dummy; } ;
struct net_device_context {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NVSP_STAT_FAIL ; 
 int NVSP_STAT_SUCCESS ; 
#define  RNDIS_MSG_INDICATE 132 
#define  RNDIS_MSG_INIT_C 131 
#define  RNDIS_MSG_PACKET 130 
#define  RNDIS_MSG_QUERY_C 129 
#define  RNDIS_MSG_SET_C 128 
 int /*<<< orphan*/  dump_rndis_message (struct net_device*,struct rndis_message*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,int /*<<< orphan*/ ) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_rx_status (struct net_device_context*) ; 
 int /*<<< orphan*/  netvsc_linkstatus_callback (struct net_device*,struct rndis_message*) ; 
 int rndis_filter_receive_data (struct net_device*,struct netvsc_device*,struct netvsc_channel*,struct rndis_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndis_filter_receive_response (struct net_device*,struct netvsc_device*,struct rndis_message*) ; 

int rndis_filter_receive(struct net_device *ndev,
			 struct netvsc_device *net_dev,
			 struct netvsc_channel *nvchan,
			 void *data, u32 buflen)
{
	struct net_device_context *net_device_ctx = netdev_priv(ndev);
	struct rndis_message *rndis_msg = data;

	if (netif_msg_rx_status(net_device_ctx))
		dump_rndis_message(ndev, rndis_msg);

	switch (rndis_msg->ndis_msg_type) {
	case RNDIS_MSG_PACKET:
		return rndis_filter_receive_data(ndev, net_dev, nvchan,
						 rndis_msg, buflen);
	case RNDIS_MSG_INIT_C:
	case RNDIS_MSG_QUERY_C:
	case RNDIS_MSG_SET_C:
		/* completion msgs */
		rndis_filter_receive_response(ndev, net_dev, rndis_msg);
		break;

	case RNDIS_MSG_INDICATE:
		/* notification msgs */
		netvsc_linkstatus_callback(ndev, rndis_msg);
		break;
	default:
		netdev_err(ndev,
			"unhandled rndis message (type %u len %u)\n",
			   rndis_msg->ndis_msg_type,
			   rndis_msg->msg_len);
		return NVSP_STAT_FAIL;
	}

	return NVSP_STAT_SUCCESS;
}