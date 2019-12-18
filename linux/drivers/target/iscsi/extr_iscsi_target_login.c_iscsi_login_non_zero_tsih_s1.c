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
struct iscsi_login_req {int /*<<< orphan*/  cid; } ;
struct iscsi_conn {int dummy; } ;

/* Variables and functions */
 int iscsi_login_set_conn_values (int /*<<< orphan*/ *,struct iscsi_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_login_non_zero_tsih_s1(
	struct iscsi_conn *conn,
	unsigned char *buf)
{
	struct iscsi_login_req *pdu = (struct iscsi_login_req *)buf;

	return iscsi_login_set_conn_values(NULL, conn, pdu->cid);
}