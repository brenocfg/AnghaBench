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
typedef  int /*<<< orphan*/  u32 ;
struct sa_path_rec {scalar_t__ rec_type; } ;
struct cm_req_msg {int /*<<< orphan*/  alt_remote_gid; int /*<<< orphan*/  alt_local_gid; int /*<<< orphan*/  alt_remote_lid; int /*<<< orphan*/  alt_local_lid; int /*<<< orphan*/  primary_remote_gid; int /*<<< orphan*/  primary_local_gid; int /*<<< orphan*/  primary_remote_lid; int /*<<< orphan*/  primary_local_lid; } ;

/* Variables and functions */
 scalar_t__ SA_PATH_REC_TYPE_OPA ; 
 int /*<<< orphan*/  cm_req_has_alt_path (struct cm_req_msg*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opa_get_lid_from_gid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_path_set_dlid (struct sa_path_rec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa_path_set_slid (struct sa_path_rec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cm_format_path_lid_from_req(struct cm_req_msg *req_msg,
					struct sa_path_rec *primary_path,
					struct sa_path_rec *alt_path)
{
	u32 lid;

	if (primary_path->rec_type != SA_PATH_REC_TYPE_OPA) {
		sa_path_set_dlid(primary_path,
				 ntohs(req_msg->primary_local_lid));
		sa_path_set_slid(primary_path,
				 ntohs(req_msg->primary_remote_lid));
	} else {
		lid = opa_get_lid_from_gid(&req_msg->primary_local_gid);
		sa_path_set_dlid(primary_path, lid);

		lid = opa_get_lid_from_gid(&req_msg->primary_remote_gid);
		sa_path_set_slid(primary_path, lid);
	}

	if (!cm_req_has_alt_path(req_msg))
		return;

	if (alt_path->rec_type != SA_PATH_REC_TYPE_OPA) {
		sa_path_set_dlid(alt_path, ntohs(req_msg->alt_local_lid));
		sa_path_set_slid(alt_path, ntohs(req_msg->alt_remote_lid));
	} else {
		lid = opa_get_lid_from_gid(&req_msg->alt_local_gid);
		sa_path_set_dlid(alt_path, lid);

		lid = opa_get_lid_from_gid(&req_msg->alt_remote_gid);
		sa_path_set_slid(alt_path, lid);
	}
}