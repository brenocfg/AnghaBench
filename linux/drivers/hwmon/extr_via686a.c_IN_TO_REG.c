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
 int /*<<< orphan*/  clamp_val (long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u8 IN_TO_REG(long val, int in_num)
{
	/*
	 * To avoid floating point, we multiply constants by 10 (100 for +12V).
	 * Rounding is done (120500 is actually 133000 - 12500).
	 * Remember that val is expressed in 0.001V/bit, which is why we divide
	 * by an additional 10000 (100000 for +12V): 1000 for val and 10 (100)
	 * for the constants.
	 */
	if (in_num <= 1)
		return (u8) clamp_val((val * 21024 - 1205000) / 250000, 0, 255);
	else if (in_num == 2)
		return (u8) clamp_val((val * 15737 - 1205000) / 250000, 0, 255);
	else if (in_num == 3)
		return (u8) clamp_val((val * 10108 - 1205000) / 250000, 0, 255);
	else
		return (u8) clamp_val((val * 41714 - 12050000) / 2500000, 0,
				      255);
}