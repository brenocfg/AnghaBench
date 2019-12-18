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
typedef  scalar_t__ u32 ;
struct rndis_pktinfo_id {int flag; } ;
struct rndis_packet {scalar_t__ data_offset; scalar_t__ data_len; } ;
struct TYPE_3__ {struct rndis_packet pkt; } ;
struct rndis_message {TYPE_1__ msg; } ;
struct netvsc_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ cnt; scalar_t__ is_last; } ;
struct netvsc_channel {TYPE_2__ rsc; } ;
struct net_device {int dummy; } ;
struct ndis_tcp_ip_checksum_info {int dummy; } ;
struct ndis_pkt_8021q_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE_8021Q_INFO ; 
 scalar_t__ NVSP_RSC_MAX ; 
 int NVSP_STAT_FAIL ; 
 int NVSP_STAT_SUCCESS ; 
 scalar_t__ RNDIS_HEADER_SIZE ; 
 int RNDIS_PKTINFO_1ST_FRAG ; 
 int /*<<< orphan*/  RNDIS_PKTINFO_ID ; 
 int RNDIS_PKTINFO_LAST_FRAG ; 
 int RNDIS_PKTINFO_SUBALLOC ; 
 int /*<<< orphan*/  TCPIP_CHKSUM_PKTINFO ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,scalar_t__,scalar_t__) ; 
 int netvsc_recv_callback (struct net_device*,struct netvsc_device*,struct netvsc_channel*) ; 
 void* rndis_get_ppi (struct rndis_packet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rsc_add_data (struct netvsc_channel*,struct ndis_pkt_8021q_info const*,struct ndis_tcp_ip_checksum_info const*,void*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rndis_filter_receive_data(struct net_device *ndev,
				     struct netvsc_device *nvdev,
				     struct netvsc_channel *nvchan,
				     struct rndis_message *msg,
				     u32 data_buflen)
{
	struct rndis_packet *rndis_pkt = &msg->msg.pkt;
	const struct ndis_tcp_ip_checksum_info *csum_info;
	const struct ndis_pkt_8021q_info *vlan;
	const struct rndis_pktinfo_id *pktinfo_id;
	u32 data_offset;
	void *data;
	bool rsc_more = false;
	int ret;

	/* Remove the rndis header and pass it back up the stack */
	data_offset = RNDIS_HEADER_SIZE + rndis_pkt->data_offset;

	data_buflen -= data_offset;

	/*
	 * Make sure we got a valid RNDIS message, now total_data_buflen
	 * should be the data packet size plus the trailer padding size
	 */
	if (unlikely(data_buflen < rndis_pkt->data_len)) {
		netdev_err(ndev, "rndis message buffer "
			   "overflow detected (got %u, min %u)"
			   "...dropping this message!\n",
			   data_buflen, rndis_pkt->data_len);
		return NVSP_STAT_FAIL;
	}

	vlan = rndis_get_ppi(rndis_pkt, IEEE_8021Q_INFO, 0);

	csum_info = rndis_get_ppi(rndis_pkt, TCPIP_CHKSUM_PKTINFO, 0);

	pktinfo_id = rndis_get_ppi(rndis_pkt, RNDIS_PKTINFO_ID, 1);

	data = (void *)msg + data_offset;

	/* Identify RSC frags, drop erroneous packets */
	if (pktinfo_id && (pktinfo_id->flag & RNDIS_PKTINFO_SUBALLOC)) {
		if (pktinfo_id->flag & RNDIS_PKTINFO_1ST_FRAG)
			nvchan->rsc.cnt = 0;
		else if (nvchan->rsc.cnt == 0)
			goto drop;

		rsc_more = true;

		if (pktinfo_id->flag & RNDIS_PKTINFO_LAST_FRAG)
			rsc_more = false;

		if (rsc_more && nvchan->rsc.is_last)
			goto drop;
	} else {
		nvchan->rsc.cnt = 0;
	}

	if (unlikely(nvchan->rsc.cnt >= NVSP_RSC_MAX))
		goto drop;

	/* Put data into per channel structure.
	 * Also, remove the rndis trailer padding from rndis packet message
	 * rndis_pkt->data_len tell us the real data length, we only copy
	 * the data packet to the stack, without the rndis trailer padding
	 */
	rsc_add_data(nvchan, vlan, csum_info, data, rndis_pkt->data_len);

	if (rsc_more)
		return NVSP_STAT_SUCCESS;

	ret = netvsc_recv_callback(ndev, nvdev, nvchan);
	nvchan->rsc.cnt = 0;

	return ret;

drop:
	/* Drop incomplete packet */
	nvchan->rsc.cnt = 0;
	return NVSP_STAT_FAIL;
}