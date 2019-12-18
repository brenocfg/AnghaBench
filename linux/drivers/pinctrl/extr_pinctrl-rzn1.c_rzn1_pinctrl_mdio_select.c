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
typedef  scalar_t__ u32 ;
struct rzn1_pinctrl {scalar_t__* mdio_func; TYPE_1__* lev2; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * l2_mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rzn1_pinctrl_mdio_select(struct rzn1_pinctrl *ipctl, int mdio,
				     u32 func)
{
	if (ipctl->mdio_func[mdio] >= 0 && ipctl->mdio_func[mdio] != func)
		dev_warn(ipctl->dev, "conflicting setting for mdio%d!\n", mdio);
	ipctl->mdio_func[mdio] = func;

	dev_dbg(ipctl->dev, "setting mdio%d to %u\n", mdio, func);

	writel(func, &ipctl->lev2->l2_mdio[mdio]);
}