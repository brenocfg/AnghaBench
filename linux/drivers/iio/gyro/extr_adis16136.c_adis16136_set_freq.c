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
struct adis16136 {int /*<<< orphan*/  adis; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16136_REG_SMPL_PRD ; 
 int adis_write_reg_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int adis16136_set_freq(struct adis16136 *adis16136, unsigned int freq)
{
	unsigned int t;

	t = 32768 / freq;
	if (t < 0xf)
		t = 0xf;
	else if (t > 0xffff)
		t = 0xffff;
	else
		t--;

	return adis_write_reg_16(&adis16136->adis, ADIS16136_REG_SMPL_PRD, t);
}