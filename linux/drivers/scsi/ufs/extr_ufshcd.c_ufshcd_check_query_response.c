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
struct ufshcd_lrb {int /*<<< orphan*/  ucd_rsp_ptr; } ;
struct ufs_query_res {int response; } ;
struct TYPE_3__ {struct ufs_query_res response; } ;
struct TYPE_4__ {TYPE_1__ query; } ;
struct ufs_hba {TYPE_2__ dev_cmd; } ;

/* Variables and functions */
 int UPIU_RSP_CODE_OFFSET ; 
 int ufshcd_get_rsp_upiu_result (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ufshcd_check_query_response(struct ufs_hba *hba, struct ufshcd_lrb *lrbp)
{
	struct ufs_query_res *query_res = &hba->dev_cmd.query.response;

	/* Get the UPIU response */
	query_res->response = ufshcd_get_rsp_upiu_result(lrbp->ucd_rsp_ptr) >>
				UPIU_RSP_CODE_OFFSET;
	return query_res->response;
}