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
struct mt76x02_dev {int dummy; } ;
struct beacon_bc_data {int /*<<< orphan*/ * tail; int /*<<< orphan*/  q; struct mt76x02_dev* dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct beacon_bc_data*) ; 
 int /*<<< orphan*/  mt76_hw (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76_skb_set_moredata (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_add_buffered_bc ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 

void
mt76x02_enqueue_buffered_bc(struct mt76x02_dev *dev,
			    struct beacon_bc_data *data,
			    int max_nframes)
{
	int i, nframes;

	data->dev = dev;
	__skb_queue_head_init(&data->q);

	do {
		nframes = skb_queue_len(&data->q);
		ieee80211_iterate_active_interfaces_atomic(mt76_hw(dev),
			IEEE80211_IFACE_ITER_RESUME_ALL,
			mt76x02_add_buffered_bc, data);
	} while (nframes != skb_queue_len(&data->q) &&
		 skb_queue_len(&data->q) < max_nframes);

	if (!skb_queue_len(&data->q))
		return;

	for (i = 0; i < ARRAY_SIZE(data->tail); i++) {
		if (!data->tail[i])
			continue;
		mt76_skb_set_moredata(data->tail[i], false);
	}
}