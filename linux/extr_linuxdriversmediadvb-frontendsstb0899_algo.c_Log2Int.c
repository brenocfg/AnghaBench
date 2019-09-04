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
 int abs (int) ; 

__attribute__((used)) static long Log2Int(int number)
{
	int i;

	i = 0;
	while ((1 << i) <= abs(number))
		i++;

	if (number == 0)
		i = 1;

	return i - 1;
}