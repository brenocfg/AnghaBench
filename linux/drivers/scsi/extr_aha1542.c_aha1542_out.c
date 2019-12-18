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
 int /*<<< orphan*/  CDF ; 
 int /*<<< orphan*/  DATA (unsigned int) ; 
 int /*<<< orphan*/  HACC ; 
 int /*<<< orphan*/  INTRFLAGS (unsigned int) ; 
 int /*<<< orphan*/  INTRMASK ; 
 int /*<<< orphan*/  STATUS (unsigned int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aha1542_out(unsigned int base, u8 *buf, int len)
{
	while (len--) {
		if (!wait_mask(STATUS(base), CDF, 0, CDF, 0))
			return 1;
		outb(*buf++, DATA(base));
	}
	if (!wait_mask(INTRFLAGS(base), INTRMASK, HACC, 0, 0))
		return 1;

	return 0;
}