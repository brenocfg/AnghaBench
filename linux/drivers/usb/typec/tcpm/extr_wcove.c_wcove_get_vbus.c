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
struct wcove_typec {int vbus; int /*<<< orphan*/  regmap; } ;
struct tcpc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBC_CC1_CTRL ; 
 unsigned int USBC_CC_CTRL_VBUSOK ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct wcove_typec* tcpc_to_wcove (struct tcpc_dev*) ; 

__attribute__((used)) static int wcove_get_vbus(struct tcpc_dev *tcpc)
{
	struct wcove_typec *wcove = tcpc_to_wcove(tcpc);
	unsigned int cc1ctrl;
	int ret;

	ret = regmap_read(wcove->regmap, USBC_CC1_CTRL, &cc1ctrl);
	if (ret)
		return ret;

	wcove->vbus = !!(cc1ctrl & USBC_CC_CTRL_VBUSOK);

	return wcove->vbus;
}