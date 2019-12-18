#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct TYPE_6__ {int opcode; void* selector; void* index; void* idn; } ;
struct ufs_query_res {TYPE_3__ upiu_req; } ;
struct ufs_query_req {TYPE_3__ upiu_req; } ;
struct TYPE_4__ {struct ufs_query_res response; struct ufs_query_res request; } ;
struct TYPE_5__ {TYPE_1__ query; } ;
struct ufs_hba {TYPE_2__ dev_cmd; } ;
typedef  enum query_opcode { ____Placeholder_query_opcode } query_opcode ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ufs_query_res*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ufshcd_init_query(struct ufs_hba *hba,
		struct ufs_query_req **request, struct ufs_query_res **response,
		enum query_opcode opcode, u8 idn, u8 index, u8 selector)
{
	*request = &hba->dev_cmd.query.request;
	*response = &hba->dev_cmd.query.response;
	memset(*request, 0, sizeof(struct ufs_query_req));
	memset(*response, 0, sizeof(struct ufs_query_res));
	(*request)->upiu_req.opcode = opcode;
	(*request)->upiu_req.idn = idn;
	(*request)->upiu_req.index = index;
	(*request)->upiu_req.selector = selector;
}