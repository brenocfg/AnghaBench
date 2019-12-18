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
typedef  unsigned char u8 ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 

__attribute__((used)) static void coda_scale_quant_table(u8 *q_tab, int scale)
{
	unsigned int temp;
	int i;

	for (i = 0; i < 64; i++) {
		temp = DIV_ROUND_CLOSEST((unsigned int)q_tab[i] * scale, 100);
		if (temp <= 0)
			temp = 1;
		if (temp > 255)
			temp = 255;
		q_tab[i] = (unsigned char)temp;
	}
}