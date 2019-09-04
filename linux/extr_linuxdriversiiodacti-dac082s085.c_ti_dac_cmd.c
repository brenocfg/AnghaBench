#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  spi; } ;
struct ti_dac_chip {int resolution; int* buf; TYPE_1__ mesg; } ;

/* Variables and functions */
 int spi_sync (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int ti_dac_cmd(struct ti_dac_chip *ti_dac, u8 cmd, u16 val)
{
	u8 shift = 12 - ti_dac->resolution;

	ti_dac->buf[0] = cmd | (val >> (8 - shift));
	ti_dac->buf[1] = (val << shift) & 0xff;
	return spi_sync(ti_dac->mesg.spi, &ti_dac->mesg);
}