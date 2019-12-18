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
struct iw_cm_event {void* private_data; int /*<<< orphan*/  private_data_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* kmemdup (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int copy_private_data(struct iw_cm_event *event)
{
	void *p;

	p = kmemdup(event->private_data, event->private_data_len, GFP_ATOMIC);
	if (!p)
		return -ENOMEM;
	event->private_data = p;
	return 0;
}