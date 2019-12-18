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
struct TYPE_3__ {scalar_t__ done; } ;
struct TYPE_4__ {TYPE_1__ segment; } ;
struct iscsi_tcp_conn {TYPE_2__ in; } ;

/* Variables and functions */
 scalar_t__ iscsi_tcp_hdr_recv_done ; 

inline int iscsi_tcp_recv_segment_is_hdr(struct iscsi_tcp_conn *tcp_conn)
{
	return tcp_conn->in.segment.done == iscsi_tcp_hdr_recv_done;
}