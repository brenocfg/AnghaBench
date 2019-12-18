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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct adapter {int /*<<< orphan*/  win0_lock; } ;
typedef  int /*<<< orphan*/  indices ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_EDC0 ; 
 int /*<<< orphan*/  SGE_DBQ_CTXT_BADDR_A ; 
 int /*<<< orphan*/  T4_MEMORY_READ ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int t4_memory_rw (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_eq_indices(struct adapter *adap, u16 qid, u16 *pidx, u16 *cidx)
{
	u32 addr = t4_read_reg(adap, SGE_DBQ_CTXT_BADDR_A) + 24 * qid + 8;
	__be64 indices;
	int ret;

	spin_lock(&adap->win0_lock);
	ret = t4_memory_rw(adap, 0, MEM_EDC0, addr,
			   sizeof(indices), (__be32 *)&indices,
			   T4_MEMORY_READ);
	spin_unlock(&adap->win0_lock);
	if (!ret) {
		*cidx = (be64_to_cpu(indices) >> 25) & 0xffff;
		*pidx = (be64_to_cpu(indices) >> 9) & 0xffff;
	}
	return ret;
}