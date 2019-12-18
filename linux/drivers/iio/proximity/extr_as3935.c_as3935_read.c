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
struct as3935_state {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int AS3935_ADDRESS (unsigned int) ; 
 int AS3935_READ_DATA ; 
 int spi_w8r8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int as3935_read(struct as3935_state *st, unsigned int reg, int *val)
{
	u8 cmd;
	int ret;

	cmd = (AS3935_READ_DATA | AS3935_ADDRESS(reg)) >> 8;
	ret = spi_w8r8(st->spi, cmd);
	if (ret < 0)
		return ret;
	*val = ret;

	return 0;
}