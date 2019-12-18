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
typedef  int speed_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int const*) ; 

__attribute__((used)) static speed_t pl2303_get_supported_baud_rate(speed_t baud)
{
	static const speed_t baud_sup[] = {
		75, 150, 300, 600, 1200, 1800, 2400, 3600, 4800, 7200, 9600,
		14400, 19200, 28800, 38400, 57600, 115200, 230400, 460800,
		614400, 921600, 1228800, 2457600, 3000000, 6000000
	};

	unsigned i;

	for (i = 0; i < ARRAY_SIZE(baud_sup); ++i) {
		if (baud_sup[i] > baud)
			break;
	}

	if (i == ARRAY_SIZE(baud_sup))
		baud = baud_sup[i - 1];
	else if (i > 0 && (baud_sup[i] - baud) > (baud - baud_sup[i - 1]))
		baud = baud_sup[i - 1];
	else
		baud = baud_sup[i];

	return baud;
}