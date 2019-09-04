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
struct serio {int dummy; } ;

/* Variables and functions */
 unsigned char I8042_STR_AUXDATA ; 
 int /*<<< orphan*/  dbg (char*) ; 
 scalar_t__ i8042_platform_filter (unsigned char,unsigned char,struct serio*) ; 
 int /*<<< orphan*/  i8042_suppress_kbd_ack ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i8042_filter(unsigned char data, unsigned char str,
			 struct serio *serio)
{
	if (unlikely(i8042_suppress_kbd_ack)) {
		if ((~str & I8042_STR_AUXDATA) &&
		    (data == 0xfa || data == 0xfe)) {
			i8042_suppress_kbd_ack--;
			dbg("Extra keyboard ACK - filtered out\n");
			return true;
		}
	}

	if (i8042_platform_filter && i8042_platform_filter(data, str, serio)) {
		dbg("Filtered out by platform filter\n");
		return true;
	}

	return false;
}