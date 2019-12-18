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
typedef  unsigned long u64 ;
struct pfn_array {unsigned long* pa_iova_pfn; scalar_t__ pa_nr; } ;
struct channel_program {int /*<<< orphan*/  mdev; } ;
struct ccwchain {struct pfn_array* ch_pa; struct ccw1* ch_ccw; } ;
struct ccw1 {int count; unsigned long cda; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  iova ;
typedef  unsigned long __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_IDA ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ ccw_does_data_transfer (struct ccw1*) ; 
 scalar_t__ ccw_is_idal (struct ccw1*) ; 
 int copy_from_iova (int /*<<< orphan*/ ,unsigned long*,unsigned long,int) ; 
 int idal_nr_words (void*,int) ; 
 unsigned long* kcalloc (int,int,int) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 int pfn_array_alloc (struct pfn_array*,unsigned long,int) ; 
 int /*<<< orphan*/  pfn_array_idal_create_words (struct pfn_array*,unsigned long*) ; 
 int pfn_array_pin (struct pfn_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_array_unpin_free (struct pfn_array*,int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_phys (unsigned long*) ; 

__attribute__((used)) static int ccwchain_fetch_direct(struct ccwchain *chain,
				 int idx,
				 struct channel_program *cp)
{
	struct ccw1 *ccw;
	struct pfn_array *pa;
	u64 iova;
	unsigned long *idaws;
	int ret;
	int bytes = 1;
	int idaw_nr, idal_len;
	int i;

	ccw = chain->ch_ccw + idx;

	if (ccw->count)
		bytes = ccw->count;

	/* Calculate size of IDAL */
	if (ccw_is_idal(ccw)) {
		/* Read first IDAW to see if it's 4K-aligned or not. */
		/* All subsequent IDAws will be 4K-aligned. */
		ret = copy_from_iova(cp->mdev, &iova, ccw->cda, sizeof(iova));
		if (ret)
			return ret;
	} else {
		iova = ccw->cda;
	}
	idaw_nr = idal_nr_words((void *)iova, bytes);
	idal_len = idaw_nr * sizeof(*idaws);

	/* Allocate an IDAL from host storage */
	idaws = kcalloc(idaw_nr, sizeof(*idaws), GFP_DMA | GFP_KERNEL);
	if (!idaws) {
		ret = -ENOMEM;
		goto out_init;
	}

	/*
	 * Allocate an array of pfn's for pages to pin/translate.
	 * The number of pages is actually the count of the idaws
	 * required for the data transfer, since we only only support
	 * 4K IDAWs today.
	 */
	pa = chain->ch_pa + idx;
	ret = pfn_array_alloc(pa, iova, bytes);
	if (ret < 0)
		goto out_free_idaws;

	if (ccw_is_idal(ccw)) {
		/* Copy guest IDAL into host IDAL */
		ret = copy_from_iova(cp->mdev, idaws, ccw->cda, idal_len);
		if (ret)
			goto out_unpin;

		/*
		 * Copy guest IDAWs into pfn_array, in case the memory they
		 * occupy is not contiguous.
		 */
		for (i = 0; i < idaw_nr; i++)
			pa->pa_iova_pfn[i] = idaws[i] >> PAGE_SHIFT;
	} else {
		/*
		 * No action is required here; the iova addresses in pfn_array
		 * were initialized sequentially in pfn_array_alloc() beginning
		 * with the contents of ccw->cda.
		 */
	}

	if (ccw_does_data_transfer(ccw)) {
		ret = pfn_array_pin(pa, cp->mdev);
		if (ret < 0)
			goto out_unpin;
	} else {
		pa->pa_nr = 0;
	}

	ccw->cda = (__u32) virt_to_phys(idaws);
	ccw->flags |= CCW_FLAG_IDA;

	/* Populate the IDAL with pinned/translated addresses from pfn */
	pfn_array_idal_create_words(pa, idaws);

	return 0;

out_unpin:
	pfn_array_unpin_free(pa, cp->mdev);
out_free_idaws:
	kfree(idaws);
out_init:
	ccw->cda = 0;
	return ret;
}