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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ CMOS_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ bios_pop_queue () ; 
 int /*<<< orphan*/  cmos_address ; 
 int /*<<< orphan*/  handle_key (scalar_t__) ; 

__attribute__((used)) static void poll_bios(bool discard)
{
	u8 qlen;
	u16 val;

	for (;;) {
		qlen = CMOS_READ(cmos_address);
		if (qlen == 0)
			break;
		val = bios_pop_queue();
		if (val != 0 && !discard)
			handle_key((u8)val);
	}
}