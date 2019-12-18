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
struct iscsi_node_auth {int naf_flags; } ;
struct iscsi_conn {TYPE_1__* tpg; struct iscsi_chap* auth_protocol; } ;
struct iscsi_chap {int digest_type; int id; } ;
struct TYPE_2__ {int /*<<< orphan*/  tpg_chap_id; } ;

/* Variables and functions */
#define  CHAP_DIGEST_MD5 129 
#define  CHAP_DIGEST_UNKNOWN 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NAF_PASSWORD_SET ; 
 int NAF_USERID_SET ; 
 int chap_check_algorithm (char const*) ; 
 int /*<<< orphan*/  chap_close (struct iscsi_conn*) ; 
 scalar_t__ chap_gen_challenge (struct iscsi_conn*,int,char*,unsigned int*) ; 
 struct iscsi_chap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 unsigned int sprintf (char*,char*,...) ; 

__attribute__((used)) static struct iscsi_chap *chap_server_open(
	struct iscsi_conn *conn,
	struct iscsi_node_auth *auth,
	const char *a_str,
	char *aic_str,
	unsigned int *aic_len)
{
	int ret;
	struct iscsi_chap *chap;

	if (!(auth->naf_flags & NAF_USERID_SET) ||
	    !(auth->naf_flags & NAF_PASSWORD_SET)) {
		pr_err("CHAP user or password not set for"
				" Initiator ACL\n");
		return NULL;
	}

	conn->auth_protocol = kzalloc(sizeof(struct iscsi_chap), GFP_KERNEL);
	if (!conn->auth_protocol)
		return NULL;

	chap = conn->auth_protocol;
	ret = chap_check_algorithm(a_str);
	switch (ret) {
	case CHAP_DIGEST_MD5:
		pr_debug("[server] Got CHAP_A=5\n");
		/*
		 * Send back CHAP_A set to MD5.
		*/
		*aic_len = sprintf(aic_str, "CHAP_A=5");
		*aic_len += 1;
		chap->digest_type = CHAP_DIGEST_MD5;
		pr_debug("[server] Sending CHAP_A=%d\n", chap->digest_type);
		break;
	case CHAP_DIGEST_UNKNOWN:
	default:
		pr_err("Unsupported CHAP_A value\n");
		chap_close(conn);
		return NULL;
	}

	/*
	 * Set Identifier.
	 */
	chap->id = conn->tpg->tpg_chap_id++;
	*aic_len += sprintf(aic_str + *aic_len, "CHAP_I=%d", chap->id);
	*aic_len += 1;
	pr_debug("[server] Sending CHAP_I=%d\n", chap->id);
	/*
	 * Generate Challenge.
	 */
	if (chap_gen_challenge(conn, 1, aic_str, aic_len) < 0) {
		chap_close(conn);
		return NULL;
	}

	return chap;
}