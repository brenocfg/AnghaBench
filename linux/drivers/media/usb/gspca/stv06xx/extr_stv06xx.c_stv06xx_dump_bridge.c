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
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  stv06xx_read_bridge (struct sd*,int,int*) ; 
 int /*<<< orphan*/  stv06xx_write_bridge (struct sd*,int,int) ; 

__attribute__((used)) static void stv06xx_dump_bridge(struct sd *sd)
{
	int i;
	u8 data, buf;

	pr_info("Dumping all stv06xx bridge registers\n");
	for (i = 0x1400; i < 0x160f; i++) {
		stv06xx_read_bridge(sd, i, &data);

		pr_info("Read 0x%x from address 0x%x\n", data, i);
	}

	pr_info("Testing stv06xx bridge registers for writability\n");
	for (i = 0x1400; i < 0x160f; i++) {
		stv06xx_read_bridge(sd, i, &data);
		buf = data;

		stv06xx_write_bridge(sd, i, 0xff);
		stv06xx_read_bridge(sd, i, &data);
		if (data == 0xff)
			pr_info("Register 0x%x is read/write\n", i);
		else if (data != buf)
			pr_info("Register 0x%x is read/write, but only partially\n",
				i);
		else
			pr_info("Register 0x%x is read-only\n", i);

		stv06xx_write_bridge(sd, i, buf);
	}
}