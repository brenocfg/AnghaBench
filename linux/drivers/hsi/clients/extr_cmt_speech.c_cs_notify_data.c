#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int dataind_pending; int /*<<< orphan*/  lock; int /*<<< orphan*/  dataind_queue; TYPE_1__* cl; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 TYPE_2__ cs_char_data ; 
 int /*<<< orphan*/  cs_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_pop_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cs_notify_data(u32 message, int maxlength)
{
	cs_notify(message, &cs_char_data.dataind_queue);

	spin_lock(&cs_char_data.lock);
	cs_char_data.dataind_pending++;
	while (cs_char_data.dataind_pending > maxlength &&
				!list_empty(&cs_char_data.dataind_queue)) {
		dev_dbg(&cs_char_data.cl->device, "data notification "
		"queue overrun (%u entries)\n", cs_char_data.dataind_pending);

		cs_pop_entry(&cs_char_data.dataind_queue);
		cs_char_data.dataind_pending--;
	}
	spin_unlock(&cs_char_data.lock);
}