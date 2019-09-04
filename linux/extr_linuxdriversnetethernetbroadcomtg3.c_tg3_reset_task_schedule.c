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
struct tg3 {int /*<<< orphan*/  reset_task; int /*<<< orphan*/  tg3_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TG3_FLAG_RESET_TASK_PENDING ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tg3_reset_task_schedule(struct tg3 *tp)
{
	if (!test_and_set_bit(TG3_FLAG_RESET_TASK_PENDING, tp->tg3_flags))
		schedule_work(&tp->reset_task);
}