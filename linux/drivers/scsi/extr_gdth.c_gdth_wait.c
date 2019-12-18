#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int /*<<< orphan*/  hanum; } ;
typedef  TYPE_1__ gdth_ha_str ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  __gdth_interrupt (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  gdth_delay (int) ; 
 scalar_t__ gdth_test_busy (TYPE_1__*) ; 

__attribute__((used)) static int gdth_wait(gdth_ha_str *ha, int index, u32 time)
{
    int answer_found = FALSE;
    int wait_index = 0;

    TRACE(("gdth_wait() hanum %d index %d time %d\n", ha->hanum, index, time));

    if (index == 0)
        return 1;                               /* no wait required */

    do {
	__gdth_interrupt(ha, true, &wait_index);
        if (wait_index == index) {
            answer_found = TRUE;
            break;
        }
        gdth_delay(1);
    } while (--time);

    while (gdth_test_busy(ha))
        gdth_delay(0);

    return (answer_found);
}