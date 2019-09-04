#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_3__ {int timestamp; void* param2; void* param1; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ LOG_ENTRY_T ;

/* Variables and functions */
 int LOG_ENTRIES ; 
 int /*<<< orphan*/  log_lock ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int readl (scalar_t__) ; 
 TYPE_1__* sdhost_log_buf ; 
 int sdhost_log_idx ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ timer_base ; 

__attribute__((used)) static void log_event_impl(const char *event, u32 param1, u32 param2)
{
	if (sdhost_log_buf) {
		LOG_ENTRY_T *entry;
		unsigned long flags;

		spin_lock_irqsave(&log_lock, flags);

		entry = sdhost_log_buf + sdhost_log_idx;
		memcpy(entry->event, event, 4);
		entry->timestamp = (readl(timer_base + 4) & 0x3fffffff) +
			(smp_processor_id()<<30);
		entry->param1 = param1;
		entry->param2 = param2;
		sdhost_log_idx = (sdhost_log_idx + 1) % LOG_ENTRIES;

		spin_unlock_irqrestore(&log_lock, flags);
	}
}