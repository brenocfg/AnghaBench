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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int npadch ; 

__attribute__((used)) static void k_ascii(struct vc_data *vc, unsigned char value, char up_flag)
{
	int base;

	if (up_flag)
		return;

	if (value < 10) {
		/* decimal input of code, while Alt depressed */
		base = 10;
	} else {
		/* hexadecimal input of code, while AltGr depressed */
		value -= 10;
		base = 16;
	}

	if (npadch == -1)
		npadch = value;
	else
		npadch = npadch * base + value;
}