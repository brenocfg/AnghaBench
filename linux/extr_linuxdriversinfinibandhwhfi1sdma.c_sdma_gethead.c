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
struct sdma_engine {int descq_head; int sdma_mask; int descq_cnt; int /*<<< orphan*/  this_idx; int /*<<< orphan*/  descq_tail; int /*<<< orphan*/ * head_dma; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEAD ; 
 int HFI1_CAP_IS_KSET (int /*<<< orphan*/ ) ; 
 int HFI1_HAS_SDMA_TIMEOUT ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA_HEAD_CHECK ; 
 int /*<<< orphan*/  USE_SDMA_HEAD ; 
 scalar_t__ __sdma_running (struct sdma_engine*) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ read_sde_csr (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline u16 sdma_gethead(struct sdma_engine *sde)
{
	struct hfi1_devdata *dd = sde->dd;
	int use_dmahead;
	u16 hwhead;

#ifdef CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n",
		   sde->this_idx, slashstrip(__FILE__), __LINE__, __func__);
#endif

retry:
	use_dmahead = HFI1_CAP_IS_KSET(USE_SDMA_HEAD) && __sdma_running(sde) &&
					(dd->flags & HFI1_HAS_SDMA_TIMEOUT);
	hwhead = use_dmahead ?
		(u16)le64_to_cpu(*sde->head_dma) :
		(u16)read_sde_csr(sde, SD(HEAD));

	if (unlikely(HFI1_CAP_IS_KSET(SDMA_HEAD_CHECK))) {
		u16 cnt;
		u16 swtail;
		u16 swhead;
		int sane;

		swhead = sde->descq_head & sde->sdma_mask;
		/* this code is really bad for cache line trading */
		swtail = READ_ONCE(sde->descq_tail) & sde->sdma_mask;
		cnt = sde->descq_cnt;

		if (swhead < swtail)
			/* not wrapped */
			sane = (hwhead >= swhead) & (hwhead <= swtail);
		else if (swhead > swtail)
			/* wrapped around */
			sane = ((hwhead >= swhead) && (hwhead < cnt)) ||
				(hwhead <= swtail);
		else
			/* empty */
			sane = (hwhead == swhead);

		if (unlikely(!sane)) {
			dd_dev_err(dd, "SDMA(%u) bad head (%s) hwhd=%hu swhd=%hu swtl=%hu cnt=%hu\n",
				   sde->this_idx,
				   use_dmahead ? "dma" : "kreg",
				   hwhead, swhead, swtail, cnt);
			if (use_dmahead) {
				/* try one more time, using csr */
				use_dmahead = 0;
				goto retry;
			}
			/* proceed as if no progress */
			hwhead = swhead;
		}
	}
	return hwhead;
}