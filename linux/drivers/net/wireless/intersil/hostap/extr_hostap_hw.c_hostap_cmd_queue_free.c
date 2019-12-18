#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hostap_cmd_queue {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmdlock; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  __hostap_cmd_queue_free (TYPE_1__*,struct hostap_cmd_queue*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void hostap_cmd_queue_free(local_info_t *local,
					 struct hostap_cmd_queue *entry,
					 int del_req)
{
	unsigned long flags;

	spin_lock_irqsave(&local->cmdlock, flags);
	__hostap_cmd_queue_free(local, entry, del_req);
	spin_unlock_irqrestore(&local->cmdlock, flags);
}