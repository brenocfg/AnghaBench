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
struct skb_frag_struct {int page_offset; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int nr_frags; int gso_size; struct skb_frag_struct* frags; } ;

/* Variables and functions */
 int I40E_MAX_BUFFER_TXD ; 
 int I40E_MAX_DATA_PER_TXD ; 
 scalar_t__ I40E_MAX_DATA_PER_TXD_ALIGNED ; 
 int I40E_MAX_READ_REQ_SIZE ; 
 int skb_frag_size (struct skb_frag_struct const*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

bool __i40e_chk_linearize(struct sk_buff *skb)
{
	const struct skb_frag_struct *frag, *stale;
	int nr_frags, sum;

	/* no need to check if number of frags is less than 7 */
	nr_frags = skb_shinfo(skb)->nr_frags;
	if (nr_frags < (I40E_MAX_BUFFER_TXD - 1))
		return false;

	/* We need to walk through the list and validate that each group
	 * of 6 fragments totals at least gso_size.
	 */
	nr_frags -= I40E_MAX_BUFFER_TXD - 2;
	frag = &skb_shinfo(skb)->frags[0];

	/* Initialize size to the negative value of gso_size minus 1.  We
	 * use this as the worst case scenerio in which the frag ahead
	 * of us only provides one byte which is why we are limited to 6
	 * descriptors for a single transmit as the header and previous
	 * fragment are already consuming 2 descriptors.
	 */
	sum = 1 - skb_shinfo(skb)->gso_size;

	/* Add size of frags 0 through 4 to create our initial sum */
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);

	/* Walk through fragments adding latest fragment, testing it, and
	 * then removing stale fragments from the sum.
	 */
	for (stale = &skb_shinfo(skb)->frags[0];; stale++) {
		int stale_size = skb_frag_size(stale);

		sum += skb_frag_size(frag++);

		/* The stale fragment may present us with a smaller
		 * descriptor than the actual fragment size. To account
		 * for that we need to remove all the data on the front and
		 * figure out what the remainder would be in the last
		 * descriptor associated with the fragment.
		 */
		if (stale_size > I40E_MAX_DATA_PER_TXD) {
			int align_pad = -(stale->page_offset) &
					(I40E_MAX_READ_REQ_SIZE - 1);

			sum -= align_pad;
			stale_size -= align_pad;

			do {
				sum -= I40E_MAX_DATA_PER_TXD_ALIGNED;
				stale_size -= I40E_MAX_DATA_PER_TXD_ALIGNED;
			} while (stale_size > I40E_MAX_DATA_PER_TXD);
		}

		/* if sum is negative we failed to make sufficient progress */
		if (sum < 0)
			return true;

		if (!nr_frags--)
			break;

		sum -= stale_size;
	}

	return false;
}