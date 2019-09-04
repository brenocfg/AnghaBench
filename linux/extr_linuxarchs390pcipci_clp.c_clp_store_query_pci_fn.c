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
typedef  int /*<<< orphan*/  u32 ;
struct zpci_dev {int fmb_length; int /*<<< orphan*/  util_str; int /*<<< orphan*/  pfip; int /*<<< orphan*/  uid; int /*<<< orphan*/  vfn; int /*<<< orphan*/  pft; int /*<<< orphan*/  pfgid; int /*<<< orphan*/  pchid; int /*<<< orphan*/  end_dma; int /*<<< orphan*/  start_dma; TYPE_1__* bars; } ;
struct clp_rsp_query_pci {int fmb_len; int /*<<< orphan*/  util_str; scalar_t__ util_str_avail; int /*<<< orphan*/  pfip; int /*<<< orphan*/  uid; int /*<<< orphan*/  vfn; int /*<<< orphan*/  pft; int /*<<< orphan*/  pfgid; int /*<<< orphan*/  pchid; int /*<<< orphan*/  edma; int /*<<< orphan*/  sdma; int /*<<< orphan*/ * bar_size; int /*<<< orphan*/ * bar; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int PCI_BAR_COUNT ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int clp_store_query_pci_fn(struct zpci_dev *zdev,
				  struct clp_rsp_query_pci *response)
{
	int i;

	for (i = 0; i < PCI_BAR_COUNT; i++) {
		zdev->bars[i].val = le32_to_cpu(response->bar[i]);
		zdev->bars[i].size = response->bar_size[i];
	}
	zdev->start_dma = response->sdma;
	zdev->end_dma = response->edma;
	zdev->pchid = response->pchid;
	zdev->pfgid = response->pfgid;
	zdev->pft = response->pft;
	zdev->vfn = response->vfn;
	zdev->uid = response->uid;
	zdev->fmb_length = sizeof(u32) * response->fmb_len;

	memcpy(zdev->pfip, response->pfip, sizeof(zdev->pfip));
	if (response->util_str_avail) {
		memcpy(zdev->util_str, response->util_str,
		       sizeof(zdev->util_str));
	}

	return 0;
}