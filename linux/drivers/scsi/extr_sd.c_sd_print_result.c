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
struct scsi_disk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 char const* driver_byte (int) ; 
 char const* host_byte (int) ; 
 char* scsi_driverbyte_string (int) ; 
 char* scsi_hostbyte_string (int) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk const*,char*,char const*,char const*,char const*) ; 

__attribute__((used)) static void sd_print_result(const struct scsi_disk *sdkp, const char *msg,
			    int result)
{
	const char *hb_string = scsi_hostbyte_string(result);
	const char *db_string = scsi_driverbyte_string(result);

	if (hb_string || db_string)
		sd_printk(KERN_INFO, sdkp,
			  "%s: Result: hostbyte=%s driverbyte=%s\n", msg,
			  hb_string ? hb_string : "invalid",
			  db_string ? db_string : "invalid");
	else
		sd_printk(KERN_INFO, sdkp,
			  "%s: Result: hostbyte=0x%02x driverbyte=0x%02x\n",
			  msg, host_byte(result), driver_byte(result));
}