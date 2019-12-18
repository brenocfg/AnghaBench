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
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool asus_q500a_i8042_filter(unsigned char data, unsigned char str,
			      struct serio *port)
{
	static bool extended;
	bool ret = false;

	if (str & I8042_STR_AUXDATA)
		return false;

	if (unlikely(data == 0xe1)) {
		extended = true;
		ret = true;
	} else if (unlikely(extended)) {
		extended = false;
		ret = true;
	}

	return ret;
}