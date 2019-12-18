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
typedef  int u8 ;
typedef  int u16 ;
struct ti_dac_chip {int resolution; int* buf; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int spi_write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ti_dac_cmd(struct ti_dac_chip *ti_dac, u8 power, u16 val)
{
	u8 shift = 14 - ti_dac->resolution;

	ti_dac->buf[0] = (val << shift) & 0xFF;
	ti_dac->buf[1] = (power << 6) | (val >> (8 - shift));
	return spi_write(ti_dac->spi, ti_dac->buf, 2);
}