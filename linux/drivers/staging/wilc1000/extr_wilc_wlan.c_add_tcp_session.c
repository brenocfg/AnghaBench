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
typedef  void* u32 ;
struct tcp_ack_filter {int tcp_session; TYPE_1__* ack_session_info; } ;
struct wilc_vif {struct tcp_ack_filter ack_filter; } ;
struct TYPE_2__ {void* dst_port; void* src_port; scalar_t__ bigger_ack_num; void* seq_num; } ;

/* Variables and functions */
 int MAX_TCP_SESSION ; 

__attribute__((used)) static inline void add_tcp_session(struct wilc_vif *vif, u32 src_prt,
				   u32 dst_prt, u32 seq)
{
	struct tcp_ack_filter *f = &vif->ack_filter;

	if (f->tcp_session < 2 * MAX_TCP_SESSION) {
		f->ack_session_info[f->tcp_session].seq_num = seq;
		f->ack_session_info[f->tcp_session].bigger_ack_num = 0;
		f->ack_session_info[f->tcp_session].src_port = src_prt;
		f->ack_session_info[f->tcp_session].dst_port = dst_prt;
		f->tcp_session++;
	}
}