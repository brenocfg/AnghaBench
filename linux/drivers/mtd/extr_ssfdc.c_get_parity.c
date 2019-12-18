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

__attribute__((used)) static int get_parity(int number, int size)
{
 	int k;
	int parity;

	parity = 1;
	for (k = 0; k < size; k++) {
		parity += (number >> k);
		parity &= 1;
	}
	return parity;
}