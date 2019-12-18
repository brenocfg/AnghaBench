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
struct TYPE_2__ {int /*<<< orphan*/  data_descriptor; int /*<<< orphan*/  misc; } ;
struct sbp_target_request {struct sbp_page_table_entry* pg_tbl; TYPE_1__ orb; } ;
struct sbp_page_table_entry {int dummy; } ;

/* Variables and functions */
 int CMDBLK_ORB_DATA_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMDBLK_ORB_PG_TBL_PRESENT (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  TCODE_READ_BLOCK_REQUEST ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sbp_page_table_entry*) ; 
 struct sbp_page_table_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbp2_pointer_to_addr (int /*<<< orphan*/ *) ; 
 int sbp_run_request_transaction (struct sbp_target_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sbp_page_table_entry*,int) ; 

__attribute__((used)) static int sbp_fetch_page_table(struct sbp_target_request *req)
{
	int pg_tbl_sz, ret;
	struct sbp_page_table_entry *pg_tbl;

	if (!CMDBLK_ORB_PG_TBL_PRESENT(be32_to_cpu(req->orb.misc)))
		return 0;

	pg_tbl_sz = CMDBLK_ORB_DATA_SIZE(be32_to_cpu(req->orb.misc)) *
		sizeof(struct sbp_page_table_entry);

	pg_tbl = kmalloc(pg_tbl_sz, GFP_KERNEL);
	if (!pg_tbl)
		return -ENOMEM;

	ret = sbp_run_request_transaction(req, TCODE_READ_BLOCK_REQUEST,
			sbp2_pointer_to_addr(&req->orb.data_descriptor),
			pg_tbl, pg_tbl_sz);
	if (ret != RCODE_COMPLETE) {
		kfree(pg_tbl);
		return -EIO;
	}

	req->pg_tbl = pg_tbl;
	return 0;
}