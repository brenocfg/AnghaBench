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
struct gpio_desc {int dummy; } ;
struct fixed_phy_status {int dummy; } ;
struct fixed_phy {int addr; int /*<<< orphan*/  node; struct gpio_desc* link_gpiod; struct fixed_phy_status status; int /*<<< orphan*/  seqcount; } ;
struct fixed_mdio_bus {int /*<<< orphan*/  phys; TYPE_1__* mii_bus; } ;
struct TYPE_2__ {unsigned int* irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PHY_POLL ; 
 int /*<<< orphan*/  fixed_phy_update (struct fixed_phy*) ; 
 struct fixed_phy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct fixed_mdio_bus platform_fmb ; 
 int /*<<< orphan*/  seqcount_init (int /*<<< orphan*/ *) ; 
 int swphy_validate_state (struct fixed_phy_status*) ; 

__attribute__((used)) static int fixed_phy_add_gpiod(unsigned int irq, int phy_addr,
			       struct fixed_phy_status *status,
			       struct gpio_desc *gpiod)
{
	int ret;
	struct fixed_mdio_bus *fmb = &platform_fmb;
	struct fixed_phy *fp;

	ret = swphy_validate_state(status);
	if (ret < 0)
		return ret;

	fp = kzalloc(sizeof(*fp), GFP_KERNEL);
	if (!fp)
		return -ENOMEM;

	seqcount_init(&fp->seqcount);

	if (irq != PHY_POLL)
		fmb->mii_bus->irq[phy_addr] = irq;

	fp->addr = phy_addr;
	fp->status = *status;
	fp->link_gpiod = gpiod;

	fixed_phy_update(fp);

	list_add_tail(&fp->node, &fmb->phys);

	return 0;
}