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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct opa_smp {int /*<<< orphan*/  status; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_devdata {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int OPA_AM_NBLK (int) ; 
 int OPA_NUM_PKEY_BLOCKS_PER_SMP ; 
 unsigned int OPA_PARTITION_TABLE_BLK_SIZE ; 
 int __subn_get_opa_pkeytable (struct opa_smp*,int,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int*,int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct hfi1_devdata* dd_from_ibdev (struct ib_device*) ; 
 unsigned int hfi1_get_npkeys (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int,int,...) ; 
 int reply (struct ib_mad_hdr*) ; 
 scalar_t__ set_pkeys (struct hfi1_devdata*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ smp_length_check (int,int) ; 

__attribute__((used)) static int __subn_set_opa_pkeytable(struct opa_smp *smp, u32 am, u8 *data,
				    struct ib_device *ibdev, u8 port,
				    u32 *resp_len, u32 max_len)
{
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u32 n_blocks_sent = OPA_AM_NBLK(am);
	u32 start_block = am & 0x7ff;
	u16 *p = (u16 *)data;
	__be16 *q = (__be16 *)data;
	int i;
	u16 n_blocks_avail;
	unsigned npkeys = hfi1_get_npkeys(dd);
	u32 size = 0;

	if (n_blocks_sent == 0) {
		pr_warn("OPA Get PKey AM Invalid : P = %d; B = 0x%x; N = 0x%x\n",
			port, start_block, n_blocks_sent);
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	n_blocks_avail = (u16)(npkeys / OPA_PARTITION_TABLE_BLK_SIZE) + 1;

	size = sizeof(u16) * (n_blocks_sent * OPA_PARTITION_TABLE_BLK_SIZE);

	if (smp_length_check(size, max_len)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	if (start_block + n_blocks_sent > n_blocks_avail ||
	    n_blocks_sent > OPA_NUM_PKEY_BLOCKS_PER_SMP) {
		pr_warn("OPA Set PKey AM Invalid : s 0x%x; req 0x%x; avail 0x%x; blk/smp 0x%lx\n",
			start_block, n_blocks_sent, n_blocks_avail,
			OPA_NUM_PKEY_BLOCKS_PER_SMP);
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	for (i = 0; i < n_blocks_sent * OPA_PARTITION_TABLE_BLK_SIZE; i++)
		p[i] = be16_to_cpu(q[i]);

	if (start_block == 0 && set_pkeys(dd, port, p) != 0) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	return __subn_get_opa_pkeytable(smp, am, data, ibdev, port, resp_len,
					max_len);
}