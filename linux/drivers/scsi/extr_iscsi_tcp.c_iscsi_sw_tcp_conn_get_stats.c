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
struct iscsi_tcp_conn {struct iscsi_sw_tcp_conn* dd_data; } ;
struct iscsi_sw_tcp_conn {int /*<<< orphan*/  discontiguous_hdr_cnt; int /*<<< orphan*/  sendpage_failures_cnt; } ;
struct iscsi_stats {int custom_length; TYPE_1__* custom; } ;
struct iscsi_conn {int /*<<< orphan*/  eh_abort_cnt; struct iscsi_tcp_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_tcp_conn_get_stats (struct iscsi_cls_conn*,struct iscsi_stats*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
iscsi_sw_tcp_conn_get_stats(struct iscsi_cls_conn *cls_conn,
			    struct iscsi_stats *stats)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	stats->custom_length = 3;
	strcpy(stats->custom[0].desc, "tx_sendpage_failures");
	stats->custom[0].value = tcp_sw_conn->sendpage_failures_cnt;
	strcpy(stats->custom[1].desc, "rx_discontiguous_hdr");
	stats->custom[1].value = tcp_sw_conn->discontiguous_hdr_cnt;
	strcpy(stats->custom[2].desc, "eh_abort_cnt");
	stats->custom[2].value = conn->eh_abort_cnt;

	iscsi_tcp_conn_get_stats(cls_conn, stats);
}