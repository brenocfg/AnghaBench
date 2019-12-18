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
struct sd {int dummy; } ;

/* Variables and functions */
 int S5K83A_PAGE_MAP ; 
 int /*<<< orphan*/  m5602_read_sensor (struct sd*,int,int*,int) ; 
 int /*<<< orphan*/  m5602_write_sensor (struct sd*,int,int*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static void s5k83a_dump_registers(struct sd *sd)
{
	int address;
	u8 page, old_page;
	m5602_read_sensor(sd, S5K83A_PAGE_MAP, &old_page, 1);

	for (page = 0; page < 16; page++) {
		m5602_write_sensor(sd, S5K83A_PAGE_MAP, &page, 1);
		pr_info("Dumping the s5k83a register state for page 0x%x\n",
			page);
		for (address = 0; address <= 0xff; address++) {
			u8 val = 0;
			m5602_read_sensor(sd, address, &val, 1);
			pr_info("register 0x%x contains 0x%x\n", address, val);
		}
	}
	pr_info("s5k83a register state dump complete\n");

	for (page = 0; page < 16; page++) {
		m5602_write_sensor(sd, S5K83A_PAGE_MAP, &page, 1);
		pr_info("Probing for which registers that are read/write for page 0x%x\n",
			page);
		for (address = 0; address <= 0xff; address++) {
			u8 old_val, ctrl_val, test_val = 0xff;

			m5602_read_sensor(sd, address, &old_val, 1);
			m5602_write_sensor(sd, address, &test_val, 1);
			m5602_read_sensor(sd, address, &ctrl_val, 1);

			if (ctrl_val == test_val)
				pr_info("register 0x%x is writeable\n",
					address);
			else
				pr_info("register 0x%x is read only\n",
					address);

			/* Restore original val */
			m5602_write_sensor(sd, address, &old_val, 1);
		}
	}
	pr_info("Read/write register probing complete\n");
	m5602_write_sensor(sd, S5K83A_PAGE_MAP, &old_page, 1);
}