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
struct rx_cxt {int /*<<< orphan*/  rx_free_list; int /*<<< orphan*/  free_list_lock; int /*<<< orphan*/  submit_list_lock; int /*<<< orphan*/  to_host_lock; int /*<<< orphan*/  rx_submit_list; int /*<<< orphan*/  to_host_list; } ;
struct mux_rx {int /*<<< orphan*/  free_list; } ;
struct mux_dev {int /*<<< orphan*/  work_rx; int /*<<< orphan*/  write_lock; struct rx_cxt rx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_ISSUE_NUM ; 
 struct mux_rx* alloc_mux_rx () ; 
 int /*<<< orphan*/  do_rx ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_usb(struct mux_dev *mux_dev)
{
	struct mux_rx *r;
	struct rx_cxt *rx = &mux_dev->rx;
	int ret = 0;
	int i;

	spin_lock_init(&mux_dev->write_lock);
	INIT_LIST_HEAD(&rx->to_host_list);
	INIT_LIST_HEAD(&rx->rx_submit_list);
	INIT_LIST_HEAD(&rx->rx_free_list);
	spin_lock_init(&rx->to_host_lock);
	spin_lock_init(&rx->submit_list_lock);
	spin_lock_init(&rx->free_list_lock);

	for (i = 0; i < MAX_ISSUE_NUM * 2; i++) {
		r = alloc_mux_rx();
		if (!r) {
			ret = -ENOMEM;
			break;
		}

		list_add(&r->free_list, &rx->rx_free_list);
	}

	INIT_DELAYED_WORK(&mux_dev->work_rx, do_rx);

	return ret;
}