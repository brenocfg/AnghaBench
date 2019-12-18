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
typedef  int /*<<< orphan*/  u32 ;
struct iscsi_session {int dummy; } ;
struct iscsi_conn {scalar_t__ auth_id; int /*<<< orphan*/  stat_sn; int /*<<< orphan*/  cid; struct iscsi_session* sess; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  auth_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_id_lock ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int get_random_bytes_wait (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* iscsit_global ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int iscsi_login_set_conn_values(
	struct iscsi_session *sess,
	struct iscsi_conn *conn,
	__be16 cid)
{
	int ret;
	conn->sess		= sess;
	conn->cid		= be16_to_cpu(cid);
	/*
	 * Generate a random Status sequence number (statsn) for the new
	 * iSCSI connection.
	 */
	ret = get_random_bytes_wait(&conn->stat_sn, sizeof(u32));
	if (unlikely(ret))
		return ret;

	mutex_lock(&auth_id_lock);
	conn->auth_id		= iscsit_global->auth_id++;
	mutex_unlock(&auth_id_lock);
	return 0;
}