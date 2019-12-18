#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ baddr; int /*<<< orphan*/ * hcam; int /*<<< orphan*/ * msg; } ;
struct TYPE_4__ {scalar_t__ baddr; int /*<<< orphan*/ * hcam; int /*<<< orphan*/ * msg; } ;
struct pmcraid_instance {TYPE_3__ ldn; TYPE_2__* pdev; TYPE_1__ ccn; } ;
struct pmcraid_hcam_ldn {int dummy; } ;
struct pmcraid_hcam_ccn_ext {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PMCRAID_AEN_HDR_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void pmcraid_release_hcams(struct pmcraid_instance *pinstance)
{
	if (pinstance->ccn.msg != NULL) {
		dma_free_coherent(&pinstance->pdev->dev,
				    PMCRAID_AEN_HDR_SIZE +
				    sizeof(struct pmcraid_hcam_ccn_ext),
				    pinstance->ccn.msg,
				    pinstance->ccn.baddr);

		pinstance->ccn.msg = NULL;
		pinstance->ccn.hcam = NULL;
		pinstance->ccn.baddr = 0;
	}

	if (pinstance->ldn.msg != NULL) {
		dma_free_coherent(&pinstance->pdev->dev,
				    PMCRAID_AEN_HDR_SIZE +
				    sizeof(struct pmcraid_hcam_ldn),
				    pinstance->ldn.msg,
				    pinstance->ldn.baddr);

		pinstance->ldn.msg = NULL;
		pinstance->ldn.hcam = NULL;
		pinstance->ldn.baddr = 0;
	}
}