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
struct sd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  m5602_read_bridge (struct sd*,int,unsigned char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static void m5602_dump_bridge(struct sd *sd)
{
	int i;
	for (i = 0; i < 0x80; i++) {
		unsigned char val = 0;
		m5602_read_bridge(sd, i, &val);
		pr_info("ALi m5602 address 0x%x contains 0x%x\n", i, val);
	}
	pr_info("Warning: The ALi m5602 webcam probably won't work until it's power cycled\n");
}