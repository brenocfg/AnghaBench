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

/* Variables and functions */
 scalar_t__ REG_LOOPBACK ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int fdomain_test_loopback(int base)
{
	int i;

	for (i = 0; i < 255; i++) {
		outb(i, base + REG_LOOPBACK);
		if (inb(base + REG_LOOPBACK) != i)
			return 1;
	}

	return 0;
}