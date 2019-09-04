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
struct packet_info {struct p_req_state_reply* data; } ;
struct p_req_state_reply {int /*<<< orphan*/  retcode; } ;
struct drbd_connection {int /*<<< orphan*/  ping_wait; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_WD_ST_CHG_FAIL ; 
 int /*<<< orphan*/  CONN_WD_ST_CHG_OKAY ; 
 int SS_SUCCESS ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_connection*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drbd_set_st_err_str (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int got_conn_RqSReply(struct drbd_connection *connection, struct packet_info *pi)
{
	struct p_req_state_reply *p = pi->data;
	int retcode = be32_to_cpu(p->retcode);

	if (retcode >= SS_SUCCESS) {
		set_bit(CONN_WD_ST_CHG_OKAY, &connection->flags);
	} else {
		set_bit(CONN_WD_ST_CHG_FAIL, &connection->flags);
		drbd_err(connection, "Requested state change failed by peer: %s (%d)\n",
			 drbd_set_st_err_str(retcode), retcode);
	}
	wake_up(&connection->ping_wait);

	return 0;
}