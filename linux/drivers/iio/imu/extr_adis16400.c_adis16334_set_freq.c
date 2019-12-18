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
struct adis16400_state {int /*<<< orphan*/  adis; } ;

/* Variables and functions */
 unsigned int ADIS16334_RATE_DIV_SHIFT ; 
 unsigned int ADIS16334_RATE_INT_CLK ; 
 int /*<<< orphan*/  ADIS16400_SMPL_PRD ; 
 int adis_write_reg_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int ilog2 (int) ; 

__attribute__((used)) static int adis16334_set_freq(struct adis16400_state *st, unsigned int freq)
{
	unsigned int t;

	if (freq < 819200)
		t = ilog2(819200 / freq);
	else
		t = 0;

	if (t > 0x31)
		t = 0x31;

	t <<= ADIS16334_RATE_DIV_SHIFT;
	t |= ADIS16334_RATE_INT_CLK;

	return adis_write_reg_16(&st->adis, ADIS16400_SMPL_PRD, t);
}