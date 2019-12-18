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
struct wil_tid_ampdu_rx {int /*<<< orphan*/  head_seq_num; scalar_t__* reorder_buf; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int reorder_index (struct wil_tid_ampdu_rx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_release_reorder_frame (struct net_device*,struct wil_tid_ampdu_rx*,int) ; 

__attribute__((used)) static void wil_reorder_release(struct net_device *ndev,
				struct wil_tid_ampdu_rx *r)
{
	int index = reorder_index(r, r->head_seq_num);

	while (r->reorder_buf[index]) {
		wil_release_reorder_frame(ndev, r, index);
		index = reorder_index(r, r->head_seq_num);
	}
}