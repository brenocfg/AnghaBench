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
typedef  int u64 ;
typedef  scalar_t__ bte_result_t ;

/* Variables and functions */
 scalar_t__ BTEFAIL_NOTAVAIL ; 
 scalar_t__ BTE_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int L1_CACHE_ALIGN (int) ; 
 int L1_CACHE_BYTES ; 
 int L1_CACHE_MASK ; 
 int /*<<< orphan*/  __va (int) ; 
 scalar_t__ bte_copy (int,int,int,int,int /*<<< orphan*/ *) ; 
 int ia64_tpa (unsigned long) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 

bte_result_t bte_unaligned_copy(u64 src, u64 dest, u64 len, u64 mode)
{
	int destFirstCacheOffset;
	u64 headBteSource;
	u64 headBteLen;
	u64 headBcopySrcOffset;
	u64 headBcopyDest;
	u64 headBcopyLen;
	u64 footBteSource;
	u64 footBteLen;
	u64 footBcopyDest;
	u64 footBcopyLen;
	bte_result_t rv;
	char *bteBlock, *bteBlock_unaligned;

	if (len == 0) {
		return BTE_SUCCESS;
	}

	/* temporary buffer used during unaligned transfers */
	bteBlock_unaligned = kmalloc(len + 3 * L1_CACHE_BYTES, GFP_KERNEL);
	if (bteBlock_unaligned == NULL) {
		return BTEFAIL_NOTAVAIL;
	}
	bteBlock = (char *)L1_CACHE_ALIGN((u64) bteBlock_unaligned);

	headBcopySrcOffset = src & L1_CACHE_MASK;
	destFirstCacheOffset = dest & L1_CACHE_MASK;

	/*
	 * At this point, the transfer is broken into
	 * (up to) three sections.  The first section is
	 * from the start address to the first physical
	 * cache line, the second is from the first physical
	 * cache line to the last complete cache line,
	 * and the third is from the last cache line to the
	 * end of the buffer.  The first and third sections
	 * are handled by bte copying into a temporary buffer
	 * and then bcopy'ing the necessary section into the
	 * final location.  The middle section is handled with
	 * a standard bte copy.
	 *
	 * One nasty exception to the above rule is when the
	 * source and destination are not symmetrically
	 * mis-aligned.  If the source offset from the first
	 * cache line is different from the destination offset,
	 * we make the first section be the entire transfer
	 * and the bcopy the entire block into place.
	 */
	if (headBcopySrcOffset == destFirstCacheOffset) {

		/*
		 * Both the source and destination are the same
		 * distance from a cache line boundary so we can
		 * use the bte to transfer the bulk of the
		 * data.
		 */
		headBteSource = src & ~L1_CACHE_MASK;
		headBcopyDest = dest;
		if (headBcopySrcOffset) {
			headBcopyLen =
			    (len >
			     (L1_CACHE_BYTES -
			      headBcopySrcOffset) ? L1_CACHE_BYTES
			     - headBcopySrcOffset : len);
			headBteLen = L1_CACHE_BYTES;
		} else {
			headBcopyLen = 0;
			headBteLen = 0;
		}

		if (len > headBcopyLen) {
			footBcopyLen = (len - headBcopyLen) & L1_CACHE_MASK;
			footBteLen = L1_CACHE_BYTES;

			footBteSource = src + len - footBcopyLen;
			footBcopyDest = dest + len - footBcopyLen;

			if (footBcopyDest == (headBcopyDest + headBcopyLen)) {
				/*
				 * We have two contiguous bcopy
				 * blocks.  Merge them.
				 */
				headBcopyLen += footBcopyLen;
				headBteLen += footBteLen;
			} else if (footBcopyLen > 0) {
				rv = bte_copy(footBteSource,
					      ia64_tpa((unsigned long)bteBlock),
					      footBteLen, mode, NULL);
				if (rv != BTE_SUCCESS) {
					kfree(bteBlock_unaligned);
					return rv;
				}

				memcpy(__va(footBcopyDest),
				       (char *)bteBlock, footBcopyLen);
			}
		} else {
			footBcopyLen = 0;
			footBteLen = 0;
		}

		if (len > (headBcopyLen + footBcopyLen)) {
			/* now transfer the middle. */
			rv = bte_copy((src + headBcopyLen),
				      (dest +
				       headBcopyLen),
				      (len - headBcopyLen -
				       footBcopyLen), mode, NULL);
			if (rv != BTE_SUCCESS) {
				kfree(bteBlock_unaligned);
				return rv;
			}

		}
	} else {

		/*
		 * The transfer is not symmetric, we will
		 * allocate a buffer large enough for all the
		 * data, bte_copy into that buffer and then
		 * bcopy to the destination.
		 */

		headBcopySrcOffset = src & L1_CACHE_MASK;
		headBcopyDest = dest;
		headBcopyLen = len;

		headBteSource = src - headBcopySrcOffset;
		/* Add the leading and trailing bytes from source */
		headBteLen = L1_CACHE_ALIGN(len + headBcopySrcOffset);
	}

	if (headBcopyLen > 0) {
		rv = bte_copy(headBteSource,
			      ia64_tpa((unsigned long)bteBlock), headBteLen,
			      mode, NULL);
		if (rv != BTE_SUCCESS) {
			kfree(bteBlock_unaligned);
			return rv;
		}

		memcpy(__va(headBcopyDest), ((char *)bteBlock +
					     headBcopySrcOffset), headBcopyLen);
	}
	kfree(bteBlock_unaligned);
	return BTE_SUCCESS;
}