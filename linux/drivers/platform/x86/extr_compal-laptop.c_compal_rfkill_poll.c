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
typedef  int u8 ;
struct rfkill {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIRELESS_ADDR ; 
 int WIRELESS_KILLSWITCH ; 
 int ec_read_u8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_set_hw_state (struct rfkill*,int) ; 

__attribute__((used)) static void compal_rfkill_poll(struct rfkill *rfkill, void *data)
{
	u8 result = ec_read_u8(WIRELESS_ADDR);
	bool hw_blocked = !(result & WIRELESS_KILLSWITCH);
	rfkill_set_hw_state(rfkill, hw_blocked);
}