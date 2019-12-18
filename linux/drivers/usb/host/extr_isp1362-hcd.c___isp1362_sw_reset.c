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
struct isp1362_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCCMDSTAT ; 
 int /*<<< orphan*/  HCSWRES ; 
 int /*<<< orphan*/  HCSWRES_MAGIC ; 
 int OHCI_HCR ; 
 int isp1362_read_reg32 (struct isp1362_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1362_write_reg16 (struct isp1362_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1362_write_reg32 (struct isp1362_hcd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void __isp1362_sw_reset(struct isp1362_hcd *isp1362_hcd)
{
	int tmp = 20;

	isp1362_write_reg16(isp1362_hcd, HCSWRES, HCSWRES_MAGIC);
	isp1362_write_reg32(isp1362_hcd, HCCMDSTAT, OHCI_HCR);
	while (--tmp) {
		mdelay(1);
		if (!(isp1362_read_reg32(isp1362_hcd, HCCMDSTAT) & OHCI_HCR))
			break;
	}
	if (!tmp)
		pr_err("Software reset timeout\n");
}