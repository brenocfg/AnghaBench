#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  send_int_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  sync_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ vmbus_connection ; 

__attribute__((used)) static inline void vmbus_send_interrupt(u32 relid)
{
	sync_set_bit(relid, vmbus_connection.send_int_page);
}