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
struct i40e_pf {int /*<<< orphan*/  fd_ip4_filter_cnt; int /*<<< orphan*/  fd_sctp4_filter_cnt; int /*<<< orphan*/  fd_udp4_filter_cnt; int /*<<< orphan*/  fd_tcp4_filter_cnt; scalar_t__ fd_inv; int /*<<< orphan*/  fdir_pf_active_filters; } ;
struct i40e_fdir_filter {int flow_type; int /*<<< orphan*/  fdir_node; int /*<<< orphan*/  ip4_proto; } ;

/* Variables and functions */
#define  IPPROTO_IP 135 
#define  IPPROTO_SCTP 134 
#define  IPPROTO_TCP 133 
#define  IPPROTO_UDP 132 
#define  IP_USER_FLOW 131 
#define  SCTP_V4_FLOW 130 
#define  TCP_V4_FLOW 129 
#define  UDP_V4_FLOW 128 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct i40e_fdir_filter*) ; 

__attribute__((used)) static void i40e_delete_invalid_filter(struct i40e_pf *pf,
				       struct i40e_fdir_filter *filter)
{
	/* Update counters */
	pf->fdir_pf_active_filters--;
	pf->fd_inv = 0;

	switch (filter->flow_type) {
	case TCP_V4_FLOW:
		pf->fd_tcp4_filter_cnt--;
		break;
	case UDP_V4_FLOW:
		pf->fd_udp4_filter_cnt--;
		break;
	case SCTP_V4_FLOW:
		pf->fd_sctp4_filter_cnt--;
		break;
	case IP_USER_FLOW:
		switch (filter->ip4_proto) {
		case IPPROTO_TCP:
			pf->fd_tcp4_filter_cnt--;
			break;
		case IPPROTO_UDP:
			pf->fd_udp4_filter_cnt--;
			break;
		case IPPROTO_SCTP:
			pf->fd_sctp4_filter_cnt--;
			break;
		case IPPROTO_IP:
			pf->fd_ip4_filter_cnt--;
			break;
		}
		break;
	}

	/* Remove the filter from the list and free memory */
	hlist_del(&filter->fdir_node);
	kfree(filter);
}