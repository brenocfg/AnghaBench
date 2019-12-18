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
struct TYPE_4__ {int /*<<< orphan*/  port; int /*<<< orphan*/  node; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; int /*<<< orphan*/  node; int /*<<< orphan*/  instance; int /*<<< orphan*/  service; } ;
struct qrtr_ctrl_pkt {TYPE_2__ client; TYPE_1__ server; int /*<<< orphan*/  cmd; } ;
struct qmi_handle {int dummy; } ;

/* Variables and functions */
#define  QRTR_TYPE_BYE 131 
#define  QRTR_TYPE_DEL_CLIENT 130 
#define  QRTR_TYPE_DEL_SERVER 129 
#define  QRTR_TYPE_NEW_SERVER 128 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  qmi_recv_bye (struct qmi_handle*,int) ; 
 int /*<<< orphan*/  qmi_recv_del_client (struct qmi_handle*,int,int) ; 
 int /*<<< orphan*/  qmi_recv_del_server (struct qmi_handle*,int,int) ; 
 int /*<<< orphan*/  qmi_recv_new_server (struct qmi_handle*,int,int,int,int) ; 

__attribute__((used)) static void qmi_recv_ctrl_pkt(struct qmi_handle *qmi,
			      const void *buf, size_t len)
{
	const struct qrtr_ctrl_pkt *pkt = buf;

	if (len < sizeof(struct qrtr_ctrl_pkt)) {
		pr_debug("ignoring short control packet\n");
		return;
	}

	switch (le32_to_cpu(pkt->cmd)) {
	case QRTR_TYPE_BYE:
		qmi_recv_bye(qmi, le32_to_cpu(pkt->client.node));
		break;
	case QRTR_TYPE_NEW_SERVER:
		qmi_recv_new_server(qmi,
				    le32_to_cpu(pkt->server.service),
				    le32_to_cpu(pkt->server.instance),
				    le32_to_cpu(pkt->server.node),
				    le32_to_cpu(pkt->server.port));
		break;
	case QRTR_TYPE_DEL_SERVER:
		qmi_recv_del_server(qmi,
				    le32_to_cpu(pkt->server.node),
				    le32_to_cpu(pkt->server.port));
		break;
	case QRTR_TYPE_DEL_CLIENT:
		qmi_recv_del_client(qmi,
				    le32_to_cpu(pkt->client.node),
				    le32_to_cpu(pkt->client.port));
		break;
	}
}