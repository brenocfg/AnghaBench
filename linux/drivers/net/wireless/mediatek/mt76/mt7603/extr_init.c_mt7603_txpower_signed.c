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
 int BIT (int) ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt7603_txpower_signed(int val)
{
	bool sign = val & BIT(6);

	if (!(val & BIT(7)))
		return 0;

	val &= GENMASK(5, 0);
	if (!sign)
		val = -val;

	return val;
}