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
struct gb_bootrom {int next_request; int /*<<< orphan*/  dwork; } ;
typedef  enum next_request_type { ____Placeholder_next_request_type } next_request_type ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gb_bootrom_set_timeout(struct gb_bootrom *bootrom,
				   enum next_request_type next,
				   unsigned long timeout)
{
	bootrom->next_request = next;
	schedule_delayed_work(&bootrom->dwork, msecs_to_jiffies(timeout));
}