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
struct wil_rx_buff {int id; int /*<<< orphan*/  list; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {size_t size; struct wil_rx_buff* buff_arr; struct list_head free; struct list_head active; } ;
struct wil6210_priv {TYPE_1__ rx_buff_mgmt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 struct wil_rx_buff* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static int wil_init_rx_buff_arr(struct wil6210_priv *wil,
				size_t size)
{
	struct wil_rx_buff *buff_arr;
	struct list_head *active = &wil->rx_buff_mgmt.active;
	struct list_head *free = &wil->rx_buff_mgmt.free;
	int i;

	wil->rx_buff_mgmt.buff_arr = kcalloc(size + 1,
					     sizeof(struct wil_rx_buff),
					     GFP_KERNEL);
	if (!wil->rx_buff_mgmt.buff_arr)
		return -ENOMEM;

	/* Set list heads */
	INIT_LIST_HEAD(active);
	INIT_LIST_HEAD(free);

	/* Linkify the list.
	 * buffer id 0 should not be used (marks invalid id).
	 */
	buff_arr = wil->rx_buff_mgmt.buff_arr;
	for (i = 1; i <= size; i++) {
		list_add(&buff_arr[i].list, free);
		buff_arr[i].id = i;
	}

	wil->rx_buff_mgmt.size = size + 1;

	return 0;
}