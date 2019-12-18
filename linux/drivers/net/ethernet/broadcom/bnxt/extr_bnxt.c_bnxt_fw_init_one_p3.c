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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt {int flags; int /*<<< orphan*/  wol; struct pci_dev* pdev; } ;

/* Variables and functions */
 int BNXT_FLAG_WOL_CAP ; 
 int /*<<< orphan*/  bnxt_get_wol_settings (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_coal_params_qcaps (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_set_cache_line_size (struct bnxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_set_dflt_rfs (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_set_dflt_rss_hash_type (struct bnxt*) ; 
 int /*<<< orphan*/  cache_line_size () ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_fw_init_one_p3(struct bnxt *bp)
{
	struct pci_dev *pdev = bp->pdev;

	bnxt_set_dflt_rss_hash_type(bp);
	bnxt_set_dflt_rfs(bp);

	bnxt_get_wol_settings(bp);
	if (bp->flags & BNXT_FLAG_WOL_CAP)
		device_set_wakeup_enable(&pdev->dev, bp->wol);
	else
		device_set_wakeup_capable(&pdev->dev, false);

	bnxt_hwrm_set_cache_line_size(bp, cache_line_size());
	bnxt_hwrm_coal_params_qcaps(bp);
}