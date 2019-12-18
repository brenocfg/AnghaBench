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

__attribute__((used)) static inline unsigned int dml_round_to_multiple(unsigned int num,
						 unsigned int multiple,
						 bool up)
{
	unsigned int remainder;

	if (multiple == 0)
		return num;

	remainder = num % multiple;

	if (remainder == 0)
		return num;

	if (up)
		return (num + multiple - remainder);
	else
		return (num - remainder);
}