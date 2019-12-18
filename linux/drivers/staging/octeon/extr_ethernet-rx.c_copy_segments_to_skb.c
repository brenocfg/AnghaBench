#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int addr; int back; } ;
union cvmx_buf_ptr {TYPE_2__ s; } ;
struct sk_buff {int dummy; } ;
struct TYPE_7__ {int len; } ;
struct TYPE_10__ {int bufs; } ;
struct TYPE_9__ {TYPE_4__ s; } ;
struct TYPE_11__ {TYPE_1__ word1; union cvmx_buf_ptr packet_ptr; TYPE_3__ word2; } ;
typedef  TYPE_5__ cvmx_wqe_t ;

/* Variables and functions */
 int CVMX_FPA_PACKET_POOL_SIZE ; 
 scalar_t__ cvmx_phys_to_ptr (int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,scalar_t__,int) ; 

__attribute__((used)) static void copy_segments_to_skb(cvmx_wqe_t *work, struct sk_buff *skb)
{
	int segments = work->word2.s.bufs;
	union cvmx_buf_ptr segment_ptr = work->packet_ptr;
	int len = work->word1.len;
	int segment_size;

	while (segments--) {
		union cvmx_buf_ptr next_ptr;

		next_ptr = *(union cvmx_buf_ptr *)
			cvmx_phys_to_ptr(segment_ptr.s.addr - 8);

		/*
		 * Octeon Errata PKI-100: The segment size is wrong.
		 *
		 * Until it is fixed, calculate the segment size based on
		 * the packet pool buffer size.
		 * When it is fixed, the following line should be replaced
		 * with this one:
		 * int segment_size = segment_ptr.s.size;
		 */
		segment_size =
			CVMX_FPA_PACKET_POOL_SIZE -
			(segment_ptr.s.addr -
			 (((segment_ptr.s.addr >> 7) -
			   segment_ptr.s.back) << 7));

		/* Don't copy more than what is left in the packet */
		if (segment_size > len)
			segment_size = len;

		/* Copy the data into the packet */
		skb_put_data(skb, cvmx_phys_to_ptr(segment_ptr.s.addr),
			     segment_size);
		len -= segment_size;
		segment_ptr = next_ptr;
	}
}