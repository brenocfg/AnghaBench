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
typedef  int /*<<< orphan*/  u64 ;
struct pci_dev {int dummy; } ;
struct cavium_ptp {scalar_t__ reg_base; int /*<<< orphan*/  ptp_clock; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct cavium_ptp*) ; 
 scalar_t__ PTP_CLOCK_CFG ; 
 int /*<<< orphan*/  PTP_CLOCK_CFG_PTP_EN ; 
 struct cavium_ptp* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cavium_ptp_remove(struct pci_dev *pdev)
{
	struct cavium_ptp *clock = pci_get_drvdata(pdev);
	u64 clock_cfg;

	if (IS_ERR_OR_NULL(clock))
		return;

	ptp_clock_unregister(clock->ptp_clock);

	clock_cfg = readq(clock->reg_base + PTP_CLOCK_CFG);
	clock_cfg &= ~PTP_CLOCK_CFG_PTP_EN;
	writeq(clock_cfg, clock->reg_base + PTP_CLOCK_CFG);
}