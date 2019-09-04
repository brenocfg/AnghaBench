#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sky2_hw {TYPE_2__** dev; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GM_SMI_CTRL ; 
 int GM_SMI_CT_BUSY ; 
 int GM_SMI_CT_PHY_AD (int /*<<< orphan*/ ) ; 
 int GM_SMI_CT_REG_AD (int) ; 
 int /*<<< orphan*/  GM_SMI_DATA ; 
 int /*<<< orphan*/  PHY_ADDR_MARV ; 
 int PHY_RETRIES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int gma_read16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gm_phy_write(struct sky2_hw *hw, unsigned port, u16 reg, u16 val)
{
	int i;

	gma_write16(hw, port, GM_SMI_DATA, val);
	gma_write16(hw, port, GM_SMI_CTRL,
		    GM_SMI_CT_PHY_AD(PHY_ADDR_MARV) | GM_SMI_CT_REG_AD(reg));

	for (i = 0; i < PHY_RETRIES; i++) {
		u16 ctrl = gma_read16(hw, port, GM_SMI_CTRL);
		if (ctrl == 0xffff)
			goto io_error;

		if (!(ctrl & GM_SMI_CT_BUSY))
			return 0;

		udelay(10);
	}

	dev_warn(&hw->pdev->dev, "%s: phy write timeout\n", hw->dev[port]->name);
	return -ETIMEDOUT;

io_error:
	dev_err(&hw->pdev->dev, "%s: phy I/O error\n", hw->dev[port]->name);
	return -EIO;
}