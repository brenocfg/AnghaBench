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
struct ipr_resource_entry {int /*<<< orphan*/  std_inq_data; } ;

/* Variables and functions */
 scalar_t__ IPR_IS_DASD_DEVICE (int /*<<< orphan*/ ) ; 
 scalar_t__ ipr_is_af_dasd_device (struct ipr_resource_entry*) ; 
 scalar_t__ ipr_is_gscsi (struct ipr_resource_entry*) ; 

__attribute__((used)) static inline int ipr_is_scsi_disk(struct ipr_resource_entry *res)
{
	if (ipr_is_af_dasd_device(res) ||
	    (ipr_is_gscsi(res) && IPR_IS_DASD_DEVICE(res->std_inq_data)))
		return 1;
	else
		return 0;
}