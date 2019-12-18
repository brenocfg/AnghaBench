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
struct dasd_psf_prssd_data {int suborder; int /*<<< orphan*/  order; } ;
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {int retries; int expires; struct dasd_device* memdev; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; struct ccw1* cpaddr; scalar_t__ data; int /*<<< orphan*/  flags; struct dasd_device* startdev; } ;
struct ccw1 {int count; void* cda; int /*<<< orphan*/  cmd_code; int /*<<< orphan*/  flags; } ;
struct alias_lcu {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; struct dasd_psf_prssd_data* uac; } ;
typedef  scalar_t__ addr_t ;
typedef  void* __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_CC ; 
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_CQR_FLAGS_USE_ERP ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_PSF ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_RSSD ; 
 int /*<<< orphan*/  DASD_ECKD_MAGIC ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  NEED_UAC_UPDATE ; 
 int /*<<< orphan*/  PSF_ORDER_PRSSD ; 
 int PTR_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_sfree_request (struct dasd_ccw_req*,struct dasd_device*) ; 
 int dasd_sleep_on (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_smalloc_request (int /*<<< orphan*/ ,int,int,struct dasd_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_tod_clock () ; 
 int /*<<< orphan*/  memset (struct dasd_psf_prssd_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  suborder_not_supported (struct dasd_ccw_req*) ; 

__attribute__((used)) static int read_unit_address_configuration(struct dasd_device *device,
					   struct alias_lcu *lcu)
{
	struct dasd_psf_prssd_data *prssdp;
	struct dasd_ccw_req *cqr;
	struct ccw1 *ccw;
	int rc;
	unsigned long flags;

	cqr = dasd_smalloc_request(DASD_ECKD_MAGIC, 1 /* PSF */	+ 1 /* RSSD */,
				   (sizeof(struct dasd_psf_prssd_data)),
				   device, NULL);
	if (IS_ERR(cqr))
		return PTR_ERR(cqr);
	cqr->startdev = device;
	cqr->memdev = device;
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	cqr->retries = 10;
	cqr->expires = 20 * HZ;

	/* Prepare for Read Subsystem Data */
	prssdp = (struct dasd_psf_prssd_data *) cqr->data;
	memset(prssdp, 0, sizeof(struct dasd_psf_prssd_data));
	prssdp->order = PSF_ORDER_PRSSD;
	prssdp->suborder = 0x0e;	/* Read unit address configuration */
	/* all other bytes of prssdp must be zero */

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = sizeof(struct dasd_psf_prssd_data);
	ccw->flags |= CCW_FLAG_CC;
	ccw->cda = (__u32)(addr_t) prssdp;

	/* Read Subsystem Data - feature codes */
	memset(lcu->uac, 0, sizeof(*(lcu->uac)));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_RSSD;
	ccw->count = sizeof(*(lcu->uac));
	ccw->cda = (__u32)(addr_t) lcu->uac;

	cqr->buildclk = get_tod_clock();
	cqr->status = DASD_CQR_FILLED;

	/* need to unset flag here to detect race with summary unit check */
	spin_lock_irqsave(&lcu->lock, flags);
	lcu->flags &= ~NEED_UAC_UPDATE;
	spin_unlock_irqrestore(&lcu->lock, flags);

	rc = dasd_sleep_on(cqr);
	if (rc && !suborder_not_supported(cqr)) {
		spin_lock_irqsave(&lcu->lock, flags);
		lcu->flags |= NEED_UAC_UPDATE;
		spin_unlock_irqrestore(&lcu->lock, flags);
	}
	dasd_sfree_request(cqr, cqr->memdev);
	return rc;
}