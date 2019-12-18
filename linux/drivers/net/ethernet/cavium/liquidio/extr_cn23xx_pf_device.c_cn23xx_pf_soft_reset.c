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
struct octeon_device {int /*<<< orphan*/  octeon_id; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN23XX_RST_SOFT_RST ; 
 int /*<<< orphan*/  CN23XX_SLI_SCRATCH1 ; 
 int /*<<< orphan*/  CN23XX_WIN_WR_MASK_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_writeq (struct octeon_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ octeon_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cn23xx_pf_soft_reset(struct octeon_device *oct)
{
	octeon_write_csr64(oct, CN23XX_WIN_WR_MASK_REG, 0xFF);

	dev_dbg(&oct->pci_dev->dev, "OCTEON[%d]: BIST enabled for CN23XX soft reset\n",
		oct->octeon_id);

	octeon_write_csr64(oct, CN23XX_SLI_SCRATCH1, 0x1234ULL);

	/* Initiate chip-wide soft reset */
	lio_pci_readq(oct, CN23XX_RST_SOFT_RST);
	lio_pci_writeq(oct, 1, CN23XX_RST_SOFT_RST);

	/* Wait for 100ms as Octeon resets. */
	mdelay(100);

	if (octeon_read_csr64(oct, CN23XX_SLI_SCRATCH1)) {
		dev_err(&oct->pci_dev->dev, "OCTEON[%d]: Soft reset failed\n",
			oct->octeon_id);
		return 1;
	}

	dev_dbg(&oct->pci_dev->dev, "OCTEON[%d]: Reset completed\n",
		oct->octeon_id);

	/* restore the  reset value*/
	octeon_write_csr64(oct, CN23XX_WIN_WR_MASK_REG, 0xFF);

	return 0;
}