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
typedef  int u16 ;
struct mlx5_sig_err_cqe {int /*<<< orphan*/  mkey; int /*<<< orphan*/  err_offset; int /*<<< orphan*/  actual_trans_sig; int /*<<< orphan*/  expected_trans_sig; int /*<<< orphan*/  actual_reftag; int /*<<< orphan*/  expected_reftag; int /*<<< orphan*/  syndrome; } ;
struct ib_sig_err {int expected; int actual; int key; int /*<<< orphan*/  sig_err_offset; int /*<<< orphan*/  err_type; } ;

/* Variables and functions */
 int APPTAG_ERR ; 
 int GUARD_ERR ; 
 int /*<<< orphan*/  IB_SIG_BAD_APPTAG ; 
 int /*<<< orphan*/  IB_SIG_BAD_GUARD ; 
 int /*<<< orphan*/  IB_SIG_BAD_REFTAG ; 
 int REFTAG_ERR ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void get_sig_err_item(struct mlx5_sig_err_cqe *cqe,
			     struct ib_sig_err *item)
{
	u16 syndrome = be16_to_cpu(cqe->syndrome);

#define GUARD_ERR   (1 << 13)
#define APPTAG_ERR  (1 << 12)
#define REFTAG_ERR  (1 << 11)

	if (syndrome & GUARD_ERR) {
		item->err_type = IB_SIG_BAD_GUARD;
		item->expected = be32_to_cpu(cqe->expected_trans_sig) >> 16;
		item->actual = be32_to_cpu(cqe->actual_trans_sig) >> 16;
	} else
	if (syndrome & REFTAG_ERR) {
		item->err_type = IB_SIG_BAD_REFTAG;
		item->expected = be32_to_cpu(cqe->expected_reftag);
		item->actual = be32_to_cpu(cqe->actual_reftag);
	} else
	if (syndrome & APPTAG_ERR) {
		item->err_type = IB_SIG_BAD_APPTAG;
		item->expected = be32_to_cpu(cqe->expected_trans_sig) & 0xffff;
		item->actual = be32_to_cpu(cqe->actual_trans_sig) & 0xffff;
	} else {
		pr_err("Got signature completion error with bad syndrome %04x\n",
		       syndrome);
	}

	item->sig_err_offset = be64_to_cpu(cqe->err_offset);
	item->key = be32_to_cpu(cqe->mkey);
}