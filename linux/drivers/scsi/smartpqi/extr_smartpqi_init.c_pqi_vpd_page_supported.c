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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned char u16 ;
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SCSI_VPD_HEADER_SZ ; 
 int SCSI_VPD_SUPPORTED_PAGES ; 
 int VPD_PAGE ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pqi_scsi_inquiry (struct pqi_ctrl_info*,int /*<<< orphan*/ *,int,unsigned char*,unsigned char) ; 

__attribute__((used)) static bool pqi_vpd_page_supported(struct pqi_ctrl_info *ctrl_info,
	u8 *scsi3addr, u16 vpd_page)
{
	int rc;
	int i;
	int pages;
	unsigned char *buf, bufsize;

	buf = kzalloc(256, GFP_KERNEL);
	if (!buf)
		return false;

	/* Get the size of the page list first */
	rc = pqi_scsi_inquiry(ctrl_info, scsi3addr,
				VPD_PAGE | SCSI_VPD_SUPPORTED_PAGES,
				buf, SCSI_VPD_HEADER_SZ);
	if (rc != 0)
		goto exit_unsupported;

	pages = buf[3];
	if ((pages + SCSI_VPD_HEADER_SZ) <= 255)
		bufsize = pages + SCSI_VPD_HEADER_SZ;
	else
		bufsize = 255;

	/* Get the whole VPD page list */
	rc = pqi_scsi_inquiry(ctrl_info, scsi3addr,
				VPD_PAGE | SCSI_VPD_SUPPORTED_PAGES,
				buf, bufsize);
	if (rc != 0)
		goto exit_unsupported;

	pages = buf[3];
	for (i = 1; i <= pages; i++)
		if (buf[3 + i] == vpd_page)
			goto exit_supported;

exit_unsupported:
	kfree(buf);
	return false;

exit_supported:
	kfree(buf);
	return true;
}