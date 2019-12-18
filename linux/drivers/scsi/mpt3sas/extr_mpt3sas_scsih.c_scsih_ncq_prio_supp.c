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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCSI_VPD_PG_LEN ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_device_supports_vpd (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_get_vpd_page (struct scsi_device*,int,unsigned char*,int /*<<< orphan*/ ) ; 

bool scsih_ncq_prio_supp(struct scsi_device *sdev)
{
	unsigned char *buf;
	bool ncq_prio_supp = false;

	if (!scsi_device_supports_vpd(sdev))
		return ncq_prio_supp;

	buf = kmalloc(SCSI_VPD_PG_LEN, GFP_KERNEL);
	if (!buf)
		return ncq_prio_supp;

	if (!scsi_get_vpd_page(sdev, 0x89, buf, SCSI_VPD_PG_LEN))
		ncq_prio_supp = (buf[213] >> 4) & 1;

	kfree(buf);
	return ncq_prio_supp;
}