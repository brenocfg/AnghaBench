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
struct as3935_state {int* buf; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int AS3935_ADDRESS (unsigned int) ; 
 int spi_write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int as3935_write(struct as3935_state *st,
				unsigned int reg,
				unsigned int val)
{
	u8 *buf = st->buf;

	buf[0] = AS3935_ADDRESS(reg) >> 8;
	buf[1] = val;

	return spi_write(st->spi, buf, 2);
}