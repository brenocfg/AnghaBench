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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct dln2_spi {scalar_t__ speed; scalar_t__ mode; scalar_t__ bpw; } ;

/* Variables and functions */
 int dln2_spi_enable (struct dln2_spi*,int) ; 
 int dln2_spi_set_bpw (struct dln2_spi*,scalar_t__) ; 
 int dln2_spi_set_mode (struct dln2_spi*,scalar_t__) ; 
 int dln2_spi_set_speed (struct dln2_spi*,scalar_t__) ; 

__attribute__((used)) static int dln2_spi_transfer_setup(struct dln2_spi *dln2, u32 speed,
				   u8 bpw, u8 mode)
{
	int ret;
	bool bus_setup_change;

	bus_setup_change = dln2->speed != speed || dln2->mode != mode ||
			   dln2->bpw != bpw;

	if (!bus_setup_change)
		return 0;

	ret = dln2_spi_enable(dln2, false);
	if (ret < 0)
		return ret;

	if (dln2->speed != speed) {
		ret = dln2_spi_set_speed(dln2, speed);
		if (ret < 0)
			return ret;

		dln2->speed = speed;
	}

	if (dln2->mode != mode) {
		ret = dln2_spi_set_mode(dln2, mode & 0x3);
		if (ret < 0)
			return ret;

		dln2->mode = mode;
	}

	if (dln2->bpw != bpw) {
		ret = dln2_spi_set_bpw(dln2, bpw);
		if (ret < 0)
			return ret;

		dln2->bpw = bpw;
	}

	return dln2_spi_enable(dln2, true);
}