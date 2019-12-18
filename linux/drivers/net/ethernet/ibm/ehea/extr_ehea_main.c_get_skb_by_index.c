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
struct sk_buff {void* data; } ;
struct ehea_cqe {int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 int EHEA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EHEA_CACHE_LINE ; 
 int /*<<< orphan*/  EHEA_WR_ID_INDEX ; 
 int /*<<< orphan*/  prefetch (void*) ; 
 int /*<<< orphan*/  prefetchw (void*) ; 

__attribute__((used)) static inline struct sk_buff *get_skb_by_index(struct sk_buff **skb_array,
					       int arr_len,
					       struct ehea_cqe *cqe)
{
	int skb_index = EHEA_BMASK_GET(EHEA_WR_ID_INDEX, cqe->wr_id);
	struct sk_buff *skb;
	void *pref;
	int x;

	x = skb_index + 1;
	x &= (arr_len - 1);

	pref = skb_array[x];
	if (pref) {
		prefetchw(pref);
		prefetchw(pref + EHEA_CACHE_LINE);

		pref = (skb_array[x]->data);
		prefetch(pref);
		prefetch(pref + EHEA_CACHE_LINE);
		prefetch(pref + EHEA_CACHE_LINE * 2);
		prefetch(pref + EHEA_CACHE_LINE * 3);
	}

	skb = skb_array[skb_index];
	skb_array[skb_index] = NULL;
	return skb;
}