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
#define  ACCEL_1 131 
#define  ACCEL_2 130 
#define  ACCEL_3 129 
#define  ACCEL_4 128 
 unsigned char I8042_STR_AUXDATA ; 
 int /*<<< orphan*/  serio_interrupt (struct serio*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool hp_accel_i8042_filter(unsigned char data, unsigned char str,
				  struct serio *port)
{
	static bool extended;

	if (str & I8042_STR_AUXDATA)
		return false;

	if (data == 0xe0) {
		extended = true;
		return true;
	} else if (unlikely(extended)) {
		extended = false;

		switch (data) {
		case ACCEL_1:
		case ACCEL_2:
		case ACCEL_3:
		case ACCEL_4:
			return true;
		default:
			serio_interrupt(port, 0xe0, 0);
			return false;
		}
	}

	return false;
}