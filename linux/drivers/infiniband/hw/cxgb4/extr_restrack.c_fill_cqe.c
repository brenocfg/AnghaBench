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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  wrid_low; int /*<<< orphan*/  wrid_hi; } ;
struct TYPE_4__ {TYPE_1__ gen; } ;
struct t4_cqe {int /*<<< orphan*/  bits_type_ts; TYPE_2__ u; int /*<<< orphan*/  len; int /*<<< orphan*/  header; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_nl_put_driver_u32 (struct sk_buff*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_nl_put_driver_u32_hex (struct sk_buff*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_nl_put_driver_u64_hex (struct sk_buff*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_cqe(struct sk_buff *msg, struct t4_cqe *cqe, u16 idx,
		    const char *qstr)
{
	if (rdma_nl_put_driver_u32(msg, qstr, idx))
		goto err;
	if (rdma_nl_put_driver_u32_hex(msg, "header",
					 be32_to_cpu(cqe->header)))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "len", be32_to_cpu(cqe->len)))
		goto err;
	if (rdma_nl_put_driver_u32_hex(msg, "wrid_hi",
					 be32_to_cpu(cqe->u.gen.wrid_hi)))
		goto err;
	if (rdma_nl_put_driver_u32_hex(msg, "wrid_low",
					 be32_to_cpu(cqe->u.gen.wrid_low)))
		goto err;
	if (rdma_nl_put_driver_u64_hex(msg, "bits_type_ts",
					 be64_to_cpu(cqe->bits_type_ts)))
		goto err;

	return 0;

err:
	return -EMSGSIZE;
}