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
struct iscsi_param {int /*<<< orphan*/  value; } ;
struct iscsi_conn {int /*<<< orphan*/  param_list; } ;
struct cxgbit_sock {int /*<<< orphan*/  submode; struct iscsi_conn* conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC32C ; 
 int /*<<< orphan*/  CXGBIT_SUBMODE_DCRC ; 
 int /*<<< orphan*/  CXGBIT_SUBMODE_HCRC ; 
 int /*<<< orphan*/  DATADIGEST ; 
 int /*<<< orphan*/  HEADERDIGEST ; 
 scalar_t__ cxgbit_setup_conn_digest (struct cxgbit_sock*) ; 
 struct iscsi_param* iscsi_find_param_from_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgbit_set_digest(struct cxgbit_sock *csk)
{
	struct iscsi_conn *conn = csk->conn;
	struct iscsi_param *param;

	param = iscsi_find_param_from_key(HEADERDIGEST, conn->param_list);
	if (!param) {
		pr_err("param not found key %s\n", HEADERDIGEST);
		return -1;
	}

	if (!strcmp(param->value, CRC32C))
		csk->submode |= CXGBIT_SUBMODE_HCRC;

	param = iscsi_find_param_from_key(DATADIGEST, conn->param_list);
	if (!param) {
		csk->submode = 0;
		pr_err("param not found key %s\n", DATADIGEST);
		return -1;
	}

	if (!strcmp(param->value, CRC32C))
		csk->submode |= CXGBIT_SUBMODE_DCRC;

	if (cxgbit_setup_conn_digest(csk)) {
		csk->submode = 0;
		return -1;
	}

	return 0;
}