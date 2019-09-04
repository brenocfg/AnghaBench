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
 int /*<<< orphan*/  cfag12864b_cs1 (int) ; 
 int /*<<< orphan*/  cfag12864b_cs2 (int) ; 

__attribute__((used)) static void cfag12864b_setcontrollers(unsigned char first,
	unsigned char second)
{
	if (first)
		cfag12864b_cs1(0);
	else
		cfag12864b_cs1(1);

	if (second)
		cfag12864b_cs2(0);
	else
		cfag12864b_cs2(1);
}