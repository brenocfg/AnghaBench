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
typedef  int u32 ;
struct cobalt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cobalt_info (char*,...) ; 
 int cpld_read (struct cobalt*,int) ; 

__attribute__((used)) static void cpld_info_ver3(struct cobalt *cobalt)
{
	u32 rd;
	u32 tmp;

	cobalt_info("CPLD System control register (read/write)\n");
	cobalt_info("\t\tSystem control:  0x%04x (0x0f00)\n",
		    cpld_read(cobalt, 0));
	cobalt_info("CPLD Clock control register (read/write)\n");
	cobalt_info("\t\tClock control:   0x%04x (0x0000)\n",
		    cpld_read(cobalt, 0x04));
	cobalt_info("CPLD HSMA Clk Osc register (read/write) - Must set wr trigger to load default values\n");
	cobalt_info("\t\tRegister #7:\t0x%04x (0x0022)\n",
		    cpld_read(cobalt, 0x08));
	cobalt_info("\t\tRegister #8:\t0x%04x (0x0047)\n",
		    cpld_read(cobalt, 0x0c));
	cobalt_info("\t\tRegister #9:\t0x%04x (0x00fa)\n",
		    cpld_read(cobalt, 0x10));
	cobalt_info("\t\tRegister #10:\t0x%04x (0x0061)\n",
		    cpld_read(cobalt, 0x14));
	cobalt_info("\t\tRegister #11:\t0x%04x (0x001e)\n",
		    cpld_read(cobalt, 0x18));
	cobalt_info("\t\tRegister #12:\t0x%04x (0x0045)\n",
		    cpld_read(cobalt, 0x1c));
	cobalt_info("\t\tRegister #135:\t0x%04x\n",
		    cpld_read(cobalt, 0x20));
	cobalt_info("\t\tRegister #137:\t0x%04x\n",
		    cpld_read(cobalt, 0x24));
	cobalt_info("CPLD System status register (read only)\n");
	cobalt_info("\t\tSystem status:  0x%04x\n",
		    cpld_read(cobalt, 0x28));
	cobalt_info("CPLD MAXII info register (read only)\n");
	cobalt_info("\t\tBoard serial number:     0x%04x\n",
		    cpld_read(cobalt, 0x2c));
	cobalt_info("\t\tMAXII program revision:  0x%04x\n",
		    cpld_read(cobalt, 0x30));
	cobalt_info("CPLD temp and voltage ADT7411 registers (read only)\n");
	cobalt_info("\t\tBoard temperature:  %u Celsius\n",
		    cpld_read(cobalt, 0x34) / 4);
	cobalt_info("\t\tFPGA temperature:   %u Celsius\n",
		    cpld_read(cobalt, 0x38) / 4);
	rd = cpld_read(cobalt, 0x3c);
	tmp = (rd * 33 * 1000) / (483 * 10);
	cobalt_info("\t\tVDD 3V3:      %u,%03uV\n", tmp / 1000, tmp % 1000);
	rd = cpld_read(cobalt, 0x40);
	tmp = (rd * 74 * 2197) / (27 * 1000);
	cobalt_info("\t\tADC ch3 5V:   %u,%03uV\n", tmp / 1000, tmp % 1000);
	rd = cpld_read(cobalt, 0x44);
	tmp = (rd * 74 * 2197) / (47 * 1000);
	cobalt_info("\t\tADC ch4 3V:   %u,%03uV\n", tmp / 1000, tmp % 1000);
	rd = cpld_read(cobalt, 0x48);
	tmp = (rd * 57 * 2197) / (47 * 1000);
	cobalt_info("\t\tADC ch5 2V5:  %u,%03uV\n", tmp / 1000, tmp % 1000);
	rd = cpld_read(cobalt, 0x4c);
	tmp = (rd * 2197) / 1000;
	cobalt_info("\t\tADC ch6 1V8:  %u,%03uV\n", tmp / 1000, tmp % 1000);
	rd = cpld_read(cobalt, 0x50);
	tmp = (rd * 2197) / 1000;
	cobalt_info("\t\tADC ch7 1V5:  %u,%03uV\n", tmp / 1000, tmp % 1000);
	rd = cpld_read(cobalt, 0x54);
	tmp = (rd * 2197) / 1000;
	cobalt_info("\t\tADC ch8 0V9:  %u,%03uV\n", tmp / 1000, tmp % 1000);
}