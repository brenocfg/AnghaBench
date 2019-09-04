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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 int HEADER_BDCOUNT_MAX ; 
 int /*<<< orphan*/  flexrm_header_desc (int,int,int,int,int,int) ; 
 scalar_t__ flexrm_is_next_table_desc (void*) ; 
 int /*<<< orphan*/  flexrm_write_desc (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flexrm_enqueue_desc(u32 nhpos, u32 nhcnt, u32 reqid,
				 u64 desc, void **desc_ptr, u32 *toggle,
				 void *start_desc, void *end_desc)
{
	u64 d;
	u32 nhavail, _toggle, _startpkt, _endpkt, _bdcount;

	/* Sanity check */
	if (nhcnt <= nhpos)
		return;

	/*
	 * Each request or packet start with a HEADER descriptor followed
	 * by one or more non-HEADER descriptors (SRC, SRCT, MSRC, DST,
	 * DSTT, MDST, IMM, and IMMT). The number of non-HEADER descriptors
	 * following a HEADER descriptor is represented by BDCOUNT field
	 * of HEADER descriptor. The max value of BDCOUNT field is 31 which
	 * means we can only have 31 non-HEADER descriptors following one
	 * HEADER descriptor.
	 *
	 * In general use, number of non-HEADER descriptors can easily go
	 * beyond 31. To tackle this situation, we have packet (or request)
	 * extenstion bits (STARTPKT and ENDPKT) in the HEADER descriptor.
	 *
	 * To use packet extension, the first HEADER descriptor of request
	 * (or packet) will have STARTPKT=1 and ENDPKT=0. The intermediate
	 * HEADER descriptors will have STARTPKT=0 and ENDPKT=0. The last
	 * HEADER descriptor will have STARTPKT=0 and ENDPKT=1. Also, the
	 * TOGGLE bit of the first HEADER will be set to invalid state to
	 * ensure that FlexRM does not start fetching descriptors till all
	 * descriptors are enqueued. The user of this function will flip
	 * the TOGGLE bit of first HEADER after all descriptors are
	 * enqueued.
	 */

	if ((nhpos % HEADER_BDCOUNT_MAX == 0) && (nhcnt - nhpos)) {
		/* Prepare the header descriptor */
		nhavail = (nhcnt - nhpos);
		_toggle = (nhpos == 0) ? !(*toggle) : (*toggle);
		_startpkt = (nhpos == 0) ? 0x1 : 0x0;
		_endpkt = (nhavail <= HEADER_BDCOUNT_MAX) ? 0x1 : 0x0;
		_bdcount = (nhavail <= HEADER_BDCOUNT_MAX) ?
				nhavail : HEADER_BDCOUNT_MAX;
		if (nhavail <= HEADER_BDCOUNT_MAX)
			_bdcount = nhavail;
		else
			_bdcount = HEADER_BDCOUNT_MAX;
		d = flexrm_header_desc(_toggle, _startpkt, _endpkt,
					_bdcount, 0x0, reqid);

		/* Write header descriptor */
		flexrm_write_desc(*desc_ptr, d);

		/* Point to next descriptor */
		*desc_ptr += sizeof(desc);
		if (*desc_ptr == end_desc)
			*desc_ptr = start_desc;

		/* Skip next pointer descriptors */
		while (flexrm_is_next_table_desc(*desc_ptr)) {
			*toggle = (*toggle) ? 0 : 1;
			*desc_ptr += sizeof(desc);
			if (*desc_ptr == end_desc)
				*desc_ptr = start_desc;
		}
	}

	/* Write desired descriptor */
	flexrm_write_desc(*desc_ptr, desc);

	/* Point to next descriptor */
	*desc_ptr += sizeof(desc);
	if (*desc_ptr == end_desc)
		*desc_ptr = start_desc;

	/* Skip next pointer descriptors */
	while (flexrm_is_next_table_desc(*desc_ptr)) {
		*toggle = (*toggle) ? 0 : 1;
		*desc_ptr += sizeof(desc);
		if (*desc_ptr == end_desc)
			*desc_ptr = start_desc;
	}
}