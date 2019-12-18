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
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_log_print_sense (struct scsi_device const*,char const*,int,unsigned char const*,int) ; 

void __scsi_print_sense(const struct scsi_device *sdev, const char *name,
			const unsigned char *sense_buffer, int sense_len)
{
	scsi_log_print_sense(sdev, name, -1, sense_buffer, sense_len);
}