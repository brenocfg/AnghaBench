#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iscsi_tcp_task {int exp_datasn; unsigned int data_offset; } ;
struct TYPE_6__ {unsigned int datalen; scalar_t__ hdr; } ;
struct iscsi_tcp_conn {TYPE_3__ in; } ;
struct iscsi_task {TYPE_2__* sc; struct iscsi_tcp_task* dd_data; } ;
struct iscsi_nopin {int dummy; } ;
struct iscsi_data_rsp {int flags; int /*<<< orphan*/  offset; int /*<<< orphan*/  datasn; } ;
struct iscsi_conn {int /*<<< orphan*/  datain_pdus_cnt; int /*<<< orphan*/  session; struct iscsi_tcp_conn* dd_data; } ;
struct TYPE_4__ {unsigned int length; } ;
struct TYPE_5__ {TYPE_1__ sdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_TCP (struct iscsi_conn*,char*,unsigned int,unsigned int,...) ; 
 int ISCSI_ERR_DATASN ; 
 int ISCSI_ERR_DATA_OFFSET ; 
 int ISCSI_FLAG_DATA_STATUS ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_update_cmdsn (int /*<<< orphan*/ ,struct iscsi_nopin*) ; 

__attribute__((used)) static int iscsi_tcp_data_in(struct iscsi_conn *conn, struct iscsi_task *task)
{
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct iscsi_tcp_task *tcp_task = task->dd_data;
	struct iscsi_data_rsp *rhdr = (struct iscsi_data_rsp *)tcp_conn->in.hdr;
	int datasn = be32_to_cpu(rhdr->datasn);
	unsigned total_in_length = task->sc->sdb.length;

	/*
	 * lib iscsi will update this in the completion handling if there
	 * is status.
	 */
	if (!(rhdr->flags & ISCSI_FLAG_DATA_STATUS))
		iscsi_update_cmdsn(conn->session, (struct iscsi_nopin*)rhdr);

	if (tcp_conn->in.datalen == 0)
		return 0;

	if (tcp_task->exp_datasn != datasn) {
		ISCSI_DBG_TCP(conn, "task->exp_datasn(%d) != rhdr->datasn(%d)"
			      "\n", tcp_task->exp_datasn, datasn);
		return ISCSI_ERR_DATASN;
	}

	tcp_task->exp_datasn++;

	tcp_task->data_offset = be32_to_cpu(rhdr->offset);
	if (tcp_task->data_offset + tcp_conn->in.datalen > total_in_length) {
		ISCSI_DBG_TCP(conn, "data_offset(%d) + data_len(%d) > "
			      "total_length_in(%d)\n", tcp_task->data_offset,
			      tcp_conn->in.datalen, total_in_length);
		return ISCSI_ERR_DATA_OFFSET;
	}

	conn->datain_pdus_cnt++;
	return 0;
}