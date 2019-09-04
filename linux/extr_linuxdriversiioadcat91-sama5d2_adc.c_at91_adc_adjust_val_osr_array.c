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
typedef  int u16 ;
struct at91_adc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91_adc_adjust_val_osr (struct at91_adc_state*,int*) ; 

__attribute__((used)) static void at91_adc_adjust_val_osr_array(struct at91_adc_state *st, void *buf,
					  int len)
{
	int i = 0, val;
	u16 *buf_u16 = (u16 *) buf;

	/*
	 * We are converting each two bytes (each sample).
	 * First convert the byte based array to u16, and convert each sample
	 * separately.
	 * Each value is two bytes in an array of chars, so to not shift
	 * more than we need, save the value separately.
	 * len is in bytes, so divide by two to get number of samples.
	 */
	while (i < len / 2) {
		val = buf_u16[i];
		at91_adc_adjust_val_osr(st, &val);
		buf_u16[i] = val;
		i++;
	}
}