#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
struct TYPE_4__ {TYPE_1__* spi; } ;
struct adis16400_state {TYPE_2__ adis; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_speed_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16400_SMPL_PRD ; 
 unsigned int ADIS16400_SMPL_PRD_TIME_BASE ; 
 int /*<<< orphan*/  ADIS16400_SPI_FAST ; 
 int /*<<< orphan*/  ADIS16400_SPI_SLOW ; 
 int adis_write_reg_8 (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int adis16400_set_freq(struct adis16400_state *st, unsigned int freq)
{
	unsigned int t;
	uint8_t val = 0;

	t = 1638404 / freq;
	if (t >= 128) {
		val |= ADIS16400_SMPL_PRD_TIME_BASE;
		t = 52851 / freq;
		if (t >= 128)
			t = 127;
	} else if (t != 0) {
		t--;
	}

	val |= t;

	if (t >= 0x0A || (val & ADIS16400_SMPL_PRD_TIME_BASE))
		st->adis.spi->max_speed_hz = ADIS16400_SPI_SLOW;
	else
		st->adis.spi->max_speed_hz = ADIS16400_SPI_FAST;

	return adis_write_reg_8(&st->adis, ADIS16400_SMPL_PRD, val);
}