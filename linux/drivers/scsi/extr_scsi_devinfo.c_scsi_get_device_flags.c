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
typedef  int /*<<< orphan*/  blist_flags_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_DEVINFO_GLOBAL ; 
 int /*<<< orphan*/  scsi_get_device_flags_keyed (struct scsi_device*,unsigned char const*,unsigned char const*,int /*<<< orphan*/ ) ; 

blist_flags_t scsi_get_device_flags(struct scsi_device *sdev,
				    const unsigned char *vendor,
				    const unsigned char *model)
{
	return scsi_get_device_flags_keyed(sdev, vendor, model,
					   SCSI_DEVINFO_GLOBAL);
}