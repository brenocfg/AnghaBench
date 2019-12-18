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
struct fir16_state_t {int* history; size_t curr_pos; int taps; int* coeffs; } ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static inline int16_t fir16(struct fir16_state_t *fir, int16_t sample)
{
	int32_t y;
	int i;
	int offset1;
	int offset2;

	fir->history[fir->curr_pos] = sample;

	offset2 = fir->curr_pos;
	offset1 = fir->taps - offset2;
	y = 0;
	for (i = fir->taps - 1; i >= offset1; i--)
		y += fir->coeffs[i] * fir->history[i - offset1];
	for (; i >= 0; i--)
		y += fir->coeffs[i] * fir->history[i + offset2];
	if (fir->curr_pos <= 0)
		fir->curr_pos = fir->taps;
	fir->curr_pos--;
	return (int16_t) (y >> 15);
}