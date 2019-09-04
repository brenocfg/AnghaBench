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
struct TYPE_3__ {char* event; int /*<<< orphan*/  param2; int /*<<< orphan*/  param1; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ LOG_ENTRY_T ;

/* Variables and functions */
 int LOG_ENTRIES ; 
 int /*<<< orphan*/  log_lock ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* sdhost_log_buf ; 
 int sdhost_log_idx ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void log_dump(void)
{
	if (sdhost_log_buf) {
		LOG_ENTRY_T *entry;
		unsigned long flags;
		int idx;

		spin_lock_irqsave(&log_lock, flags);

		idx = sdhost_log_idx;
		do {
			entry = sdhost_log_buf + idx;
			if (entry->event[0] != '\0')
				pr_info("[%08x] %.4s %x %x\n",
				       entry->timestamp,
				       entry->event,
				       entry->param1,
				       entry->param2);
			idx = (idx + 1) % LOG_ENTRIES;
		} while (idx != sdhost_log_idx);

		spin_unlock_irqrestore(&log_lock, flags);
	}
}