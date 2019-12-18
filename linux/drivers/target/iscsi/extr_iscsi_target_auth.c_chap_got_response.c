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
struct iscsi_node_auth {int dummy; } ;
struct iscsi_conn {struct iscsi_chap* auth_protocol; } ;
struct iscsi_chap {int digest_type; } ;

/* Variables and functions */
#define  CHAP_DIGEST_MD5 128 
 int /*<<< orphan*/  chap_server_compute_md5 (struct iscsi_conn*,struct iscsi_node_auth*,char*,char*,unsigned int*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int chap_got_response(
	struct iscsi_conn *conn,
	struct iscsi_node_auth *auth,
	char *nr_in_ptr,
	char *nr_out_ptr,
	unsigned int *nr_out_len)
{
	struct iscsi_chap *chap = conn->auth_protocol;

	switch (chap->digest_type) {
	case CHAP_DIGEST_MD5:
		if (chap_server_compute_md5(conn, auth, nr_in_ptr,
				nr_out_ptr, nr_out_len) < 0)
			return -1;
		return 0;
	default:
		pr_err("Unknown CHAP digest type %d!\n",
				chap->digest_type);
		return -1;
	}
}