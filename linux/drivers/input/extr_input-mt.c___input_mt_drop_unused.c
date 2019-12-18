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
struct input_mt {int num_slots; int /*<<< orphan*/ * slots; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_TRACKING_ID ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_is_used (struct input_mt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 

__attribute__((used)) static void __input_mt_drop_unused(struct input_dev *dev, struct input_mt *mt)
{
	int i;

	for (i = 0; i < mt->num_slots; i++) {
		if (!input_mt_is_used(mt, &mt->slots[i])) {
			input_mt_slot(dev, i);
			input_event(dev, EV_ABS, ABS_MT_TRACKING_ID, -1);
		}
	}
}