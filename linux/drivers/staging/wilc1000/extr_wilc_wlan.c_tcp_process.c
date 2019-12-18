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
typedef  int u32 ;
struct tcp_ack_filter {int tcp_session; TYPE_1__* ack_session_info; } ;
struct wilc_vif {struct tcp_ack_filter ack_filter; struct wilc* wilc; } ;
struct wilc {int /*<<< orphan*/  txq_spinlock; } ;
struct txq_entry_t {void* buffer; } ;
struct tcphdr {int doff; int /*<<< orphan*/  ack_seq; int /*<<< orphan*/  seq; } ;
struct net_device {int dummy; } ;
struct iphdr {scalar_t__ protocol; int ihl; int /*<<< orphan*/  tot_len; } ;
struct ethhdr {scalar_t__ h_proto; } ;
struct TYPE_2__ {int seq_num; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ IPPROTO_TCP ; 
 int MAX_TCP_SESSION ; 
 int /*<<< orphan*/  add_tcp_pending_ack (struct wilc_vif*,int,int,struct txq_entry_t*) ; 
 int /*<<< orphan*/  add_tcp_session (struct wilc_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_tcp_session (struct wilc_vif*,int,int) ; 

__attribute__((used)) static inline void tcp_process(struct net_device *dev, struct txq_entry_t *tqe)
{
	void *buffer = tqe->buffer;
	const struct ethhdr *eth_hdr_ptr = buffer;
	int i;
	unsigned long flags;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;
	struct tcp_ack_filter *f = &vif->ack_filter;
	const struct iphdr *ip_hdr_ptr;
	const struct tcphdr *tcp_hdr_ptr;
	u32 ihl, total_length, data_offset;

	spin_lock_irqsave(&wilc->txq_spinlock, flags);

	if (eth_hdr_ptr->h_proto != htons(ETH_P_IP))
		goto out;

	ip_hdr_ptr = buffer + ETH_HLEN;

	if (ip_hdr_ptr->protocol != IPPROTO_TCP)
		goto out;

	ihl = ip_hdr_ptr->ihl << 2;
	tcp_hdr_ptr = buffer + ETH_HLEN + ihl;
	total_length = ntohs(ip_hdr_ptr->tot_len);

	data_offset = tcp_hdr_ptr->doff << 2;
	if (total_length == (ihl + data_offset)) {
		u32 seq_no, ack_no;

		seq_no = ntohl(tcp_hdr_ptr->seq);
		ack_no = ntohl(tcp_hdr_ptr->ack_seq);
		for (i = 0; i < f->tcp_session; i++) {
			u32 j = f->ack_session_info[i].seq_num;

			if (i < 2 * MAX_TCP_SESSION &&
			    j == seq_no) {
				update_tcp_session(vif, i, ack_no);
				break;
			}
		}
		if (i == f->tcp_session)
			add_tcp_session(vif, 0, 0, seq_no);

		add_tcp_pending_ack(vif, ack_no, i, tqe);
	}

out:
	spin_unlock_irqrestore(&wilc->txq_spinlock, flags);
}