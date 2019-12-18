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
struct utp_task_req_desc {int /*<<< orphan*/  input_param1; int /*<<< orphan*/  req_header; } ;
struct ufs_hba {int nutrs; int /*<<< orphan*/  dev; struct utp_task_req_desc* utmrdl_base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ufshcd_upiu (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ufshcd_add_tm_upiu_trace(struct ufs_hba *hba, unsigned int tag,
		const char *str)
{
	int off = (int)tag - hba->nutrs;
	struct utp_task_req_desc *descp = &hba->utmrdl_base_addr[off];

	trace_ufshcd_upiu(dev_name(hba->dev), str, &descp->req_header,
			&descp->input_param1);
}