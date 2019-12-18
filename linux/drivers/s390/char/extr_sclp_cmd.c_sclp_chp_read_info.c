#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sclp_chp_info {int /*<<< orphan*/  configured; int /*<<< orphan*/  standby; int /*<<< orphan*/  recognized; } ;
struct TYPE_2__ {int length; int response_code; } ;
struct chp_info_sccb {int /*<<< orphan*/  configured; int /*<<< orphan*/  standby; int /*<<< orphan*/  recognized; TYPE_1__ header; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SCLP_CHP_INFO_MASK_SIZE ; 
 int /*<<< orphan*/  SCLP_CMDW_READ_CHPATH_INFORMATION ; 
 int /*<<< orphan*/  SCLP_HAS_CHP_INFO ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int sclp_sync_request (int /*<<< orphan*/ ,struct chp_info_sccb*) ; 

int sclp_chp_read_info(struct sclp_chp_info *info)
{
	struct chp_info_sccb *sccb;
	int rc;

	if (!SCLP_HAS_CHP_INFO)
		return -EOPNOTSUPP;
	/* Prepare sccb. */
	sccb = (struct chp_info_sccb *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	if (!sccb)
		return -ENOMEM;
	sccb->header.length = sizeof(*sccb);
	rc = sclp_sync_request(SCLP_CMDW_READ_CHPATH_INFORMATION, sccb);
	if (rc)
		goto out;
	if (sccb->header.response_code != 0x0010) {
		pr_warn("read channel-path info failed (response=0x%04x)\n",
			sccb->header.response_code);
		rc = -EIO;
		goto out;
	}
	memcpy(info->recognized, sccb->recognized, SCLP_CHP_INFO_MASK_SIZE);
	memcpy(info->standby, sccb->standby, SCLP_CHP_INFO_MASK_SIZE);
	memcpy(info->configured, sccb->configured, SCLP_CHP_INFO_MASK_SIZE);
out:
	free_page((unsigned long) sccb);
	return rc;
}