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
struct acpi_hest_generic_data_v300 {int validation_bits; int /*<<< orphan*/  time_stamp; } ;
typedef  int __u8 ;

/* Variables and functions */
 int ACPI_HEST_GEN_VALID_TIMESTAMP ; 
 int bcd2bin (int) ; 
 int /*<<< orphan*/  printk (char*,char const*,char*,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void cper_print_tstamp(const char *pfx,
				   struct acpi_hest_generic_data_v300 *gdata)
{
	__u8 hour, min, sec, day, mon, year, century, *timestamp;

	if (gdata->validation_bits & ACPI_HEST_GEN_VALID_TIMESTAMP) {
		timestamp = (__u8 *)&(gdata->time_stamp);
		sec       = bcd2bin(timestamp[0]);
		min       = bcd2bin(timestamp[1]);
		hour      = bcd2bin(timestamp[2]);
		day       = bcd2bin(timestamp[4]);
		mon       = bcd2bin(timestamp[5]);
		year      = bcd2bin(timestamp[6]);
		century   = bcd2bin(timestamp[7]);

		printk("%s%ststamp: %02d%02d-%02d-%02d %02d:%02d:%02d\n", pfx,
		       (timestamp[3] & 0x1 ? "precise " : "imprecise "),
		       century, year, mon, day, hour, min, sec);
	}
}