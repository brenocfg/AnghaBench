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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DATA (unsigned int) ; 
 int /*<<< orphan*/  DF ; 
 int /*<<< orphan*/  STATUS (unsigned int) ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aha1542_in(unsigned int base, u8 *buf, int len, int timeout)
{
	while (len--) {
		if (!wait_mask(STATUS(base), DF, DF, 0, timeout))
			return 1;
		*buf++ = inb(DATA(base));
	}
	return 0;
}