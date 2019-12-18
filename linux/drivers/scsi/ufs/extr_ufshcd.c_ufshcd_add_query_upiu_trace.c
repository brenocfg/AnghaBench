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
struct utp_upiu_req {int /*<<< orphan*/  qr; int /*<<< orphan*/  header; } ;
struct ufs_hba {int /*<<< orphan*/  dev; TYPE_1__* lrb; } ;
struct TYPE_2__ {struct utp_upiu_req* ucd_req_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ufshcd_upiu (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ufshcd_add_query_upiu_trace(struct ufs_hba *hba, unsigned int tag,
		const char *str)
{
	struct utp_upiu_req *rq = hba->lrb[tag].ucd_req_ptr;

	trace_ufshcd_upiu(dev_name(hba->dev), str, &rq->header, &rq->qr);
}