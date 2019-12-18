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
struct ispccdc_lsc {scalar_t__ state; int /*<<< orphan*/  table_work; int /*<<< orphan*/  free_queue; TYPE_1__* request; TYPE_1__* active; } ;
struct isp_ccdc_device {struct ispccdc_lsc lsc; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LSC_STATE_STOPPED ; 
 int /*<<< orphan*/  OMAP3_ISP_SBL_CCDC_LSC_READ ; 
 scalar_t__ __ccdc_lsc_configure (struct isp_ccdc_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  __ccdc_lsc_enable (struct isp_ccdc_device*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_sbl_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_isp_device (struct isp_ccdc_device*) ; 

__attribute__((used)) static int ccdc_lsc_enable(struct isp_ccdc_device *ccdc)
{
	struct ispccdc_lsc *lsc = &ccdc->lsc;

	if (lsc->state != LSC_STATE_STOPPED)
		return -EINVAL;

	if (lsc->active) {
		list_add_tail(&lsc->active->list, &lsc->free_queue);
		lsc->active = NULL;
	}

	if (__ccdc_lsc_configure(ccdc, lsc->request) < 0) {
		omap3isp_sbl_disable(to_isp_device(ccdc),
				OMAP3_ISP_SBL_CCDC_LSC_READ);
		list_add_tail(&lsc->request->list, &lsc->free_queue);
		lsc->request = NULL;
		goto done;
	}

	lsc->active = lsc->request;
	lsc->request = NULL;
	__ccdc_lsc_enable(ccdc, 1);

done:
	if (!list_empty(&lsc->free_queue))
		schedule_work(&lsc->table_work);

	return 0;
}