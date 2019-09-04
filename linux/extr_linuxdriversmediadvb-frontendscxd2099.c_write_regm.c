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
struct cxd {int lastaddress; unsigned int* regs; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int write_regm(struct cxd *ci, u8 reg, u8 val, u8 mask)
{
	int status = 0;
	unsigned int regval;

	if (ci->lastaddress != reg)
		status = regmap_write(ci->regmap, 0, reg);
	if (!status && reg >= 6 && reg <= 8 && mask != 0xff) {
		status = regmap_read(ci->regmap, 1, &regval);
		ci->regs[reg] = regval;
	}
	ci->lastaddress = reg;
	ci->regs[reg] = (ci->regs[reg] & (~mask)) | val;
	if (!status)
		status = regmap_write(ci->regmap, 1, ci->regs[reg]);
	if (reg == 0x20)
		ci->regs[reg] &= 0x7f;
	return status;
}