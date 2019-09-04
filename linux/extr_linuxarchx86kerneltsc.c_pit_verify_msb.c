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
 unsigned char inb (int) ; 

__attribute__((used)) static inline int pit_verify_msb(unsigned char val)
{
	/* Ignore LSB */
	inb(0x42);
	return inb(0x42) == val;
}