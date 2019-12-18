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
struct octeon_device {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_CIU_SOFT_BIST ; 
 int /*<<< orphan*/  CN6XXX_CIU_SOFT_RST ; 
 int /*<<< orphan*/  CN6XXX_SLI_SCRATCH1 ; 
 int /*<<< orphan*/  CN6XXX_WIN_WR_MASK_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_writeq (struct octeon_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ octeon_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

int lio_cn6xxx_soft_reset(struct octeon_device *oct)
{
	octeon_write_csr64(oct, CN6XXX_WIN_WR_MASK_REG, 0xFF);

	dev_dbg(&oct->pci_dev->dev, "BIST enabled for soft reset\n");

	lio_pci_writeq(oct, 1, CN6XXX_CIU_SOFT_BIST);
	octeon_write_csr64(oct, CN6XXX_SLI_SCRATCH1, 0x1234ULL);

	lio_pci_readq(oct, CN6XXX_CIU_SOFT_RST);
	lio_pci_writeq(oct, 1, CN6XXX_CIU_SOFT_RST);

	/* Wait for 10ms as Octeon resets. */
	mdelay(100);

	if (octeon_read_csr64(oct, CN6XXX_SLI_SCRATCH1)) {
		dev_err(&oct->pci_dev->dev, "Soft reset failed\n");
		return 1;
	}

	dev_dbg(&oct->pci_dev->dev, "Reset completed\n");
	octeon_write_csr64(oct, CN6XXX_WIN_WR_MASK_REG, 0xFF);

	return 0;
}