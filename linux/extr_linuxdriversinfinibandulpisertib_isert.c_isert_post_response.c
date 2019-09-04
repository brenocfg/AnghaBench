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
struct isert_conn {int /*<<< orphan*/  qp; } ;
struct TYPE_2__ {int /*<<< orphan*/  send_wr; } ;
struct isert_cmd {TYPE_1__ tx_desc; int /*<<< orphan*/  rx_desc; } ;

/* Variables and functions */
 int ib_post_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isert_err (char*,int) ; 
 int isert_post_recv (struct isert_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isert_post_response(struct isert_conn *isert_conn, struct isert_cmd *isert_cmd)
{
	int ret;

	ret = isert_post_recv(isert_conn, isert_cmd->rx_desc);
	if (ret) {
		isert_err("ib_post_recv failed with %d\n", ret);
		return ret;
	}

	ret = ib_post_send(isert_conn->qp, &isert_cmd->tx_desc.send_wr, NULL);
	if (ret) {
		isert_err("ib_post_send failed with %d\n", ret);
		return ret;
	}
	return ret;
}