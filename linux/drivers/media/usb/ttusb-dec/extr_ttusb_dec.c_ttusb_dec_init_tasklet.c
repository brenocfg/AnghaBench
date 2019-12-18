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
struct ttusb_dec {int /*<<< orphan*/  urb_tasklet; int /*<<< orphan*/  urb_frame_list; int /*<<< orphan*/  urb_frame_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ttusb_dec_process_urb_frame_list ; 

__attribute__((used)) static void ttusb_dec_init_tasklet(struct ttusb_dec *dec)
{
	spin_lock_init(&dec->urb_frame_list_lock);
	INIT_LIST_HEAD(&dec->urb_frame_list);
	tasklet_init(&dec->urb_tasklet, ttusb_dec_process_urb_frame_list,
		     (unsigned long)dec);
}