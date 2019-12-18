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
struct ctlr_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HPSA_VPD_HEADER_SZ ; 
 int HPSA_VPD_LV_STATUS ; 
 int HPSA_VPD_LV_STATUS_UNSUPPORTED ; 
 int VPD_PAGE ; 
 int hpsa_scsi_do_inquiry (struct ctlr_info*,unsigned char*,int,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  hpsa_vpd_page_supported (struct ctlr_info*,unsigned char*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_get_volume_status(struct ctlr_info *h,
					unsigned char scsi3addr[])
{
	int rc;
	int status;
	int size;
	unsigned char *buf;

	buf = kzalloc(64, GFP_KERNEL);
	if (!buf)
		return HPSA_VPD_LV_STATUS_UNSUPPORTED;

	/* Does controller have VPD for logical volume status? */
	if (!hpsa_vpd_page_supported(h, scsi3addr, HPSA_VPD_LV_STATUS))
		goto exit_failed;

	/* Get the size of the VPD return buffer */
	rc = hpsa_scsi_do_inquiry(h, scsi3addr, VPD_PAGE | HPSA_VPD_LV_STATUS,
					buf, HPSA_VPD_HEADER_SZ);
	if (rc != 0)
		goto exit_failed;
	size = buf[3];

	/* Now get the whole VPD buffer */
	rc = hpsa_scsi_do_inquiry(h, scsi3addr, VPD_PAGE | HPSA_VPD_LV_STATUS,
					buf, size + HPSA_VPD_HEADER_SZ);
	if (rc != 0)
		goto exit_failed;
	status = buf[4]; /* status byte */

	kfree(buf);
	return status;
exit_failed:
	kfree(buf);
	return HPSA_VPD_LV_STATUS_UNSUPPORTED;
}