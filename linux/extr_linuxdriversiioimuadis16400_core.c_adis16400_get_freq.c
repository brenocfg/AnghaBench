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
typedef  int uint16_t ;
struct adis16400_state {int /*<<< orphan*/  adis; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16400_SMPL_PRD ; 
 int ADIS16400_SMPL_PRD_DIV_MASK ; 
 int ADIS16400_SMPL_PRD_TIME_BASE ; 
 int adis_read_reg_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int adis16400_get_freq(struct adis16400_state *st)
{
	int sps, ret;
	uint16_t t;

	ret = adis_read_reg_16(&st->adis, ADIS16400_SMPL_PRD, &t);
	if (ret < 0)
		return ret;

	sps = (t & ADIS16400_SMPL_PRD_TIME_BASE) ? 52851 : 1638404;
	sps /= (t & ADIS16400_SMPL_PRD_DIV_MASK) + 1;

	return sps;
}