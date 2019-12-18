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
struct TYPE_3__ {int /*<<< orphan*/  hdr_buf; int /*<<< orphan*/  segment; } ;
struct iscsi_tcp_conn {TYPE_1__ in; TYPE_2__* iscsi_conn; } ;
struct iscsi_hdr {int dummy; } ;
struct TYPE_4__ {scalar_t__ hdrdgst_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_TCP (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  iscsi_segment_init_linear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_tcp_hdr_recv_done ; 

void iscsi_tcp_hdr_recv_prep(struct iscsi_tcp_conn *tcp_conn)
{
	ISCSI_DBG_TCP(tcp_conn->iscsi_conn,
		      "(%s)\n", tcp_conn->iscsi_conn->hdrdgst_en ?
		      "digest enabled" : "digest disabled");
	iscsi_segment_init_linear(&tcp_conn->in.segment,
				tcp_conn->in.hdr_buf, sizeof(struct iscsi_hdr),
				iscsi_tcp_hdr_recv_done, NULL);
}