#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_2__* desc; TYPE_1__ dev; } ;
struct lp8727_chg {TYPE_3__* chg_param; int /*<<< orphan*/  devid; } ;
struct TYPE_6__ {int eoc_level; int ichg; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP8727_CHGCTRL2 ; 
 int LP8727_ICHG_SHIFT ; 
 struct lp8727_chg* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp8727_is_charger_attached (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp8727_write_byte (struct lp8727_chg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lp8727_charger_changed(struct power_supply *psy)
{
	struct lp8727_chg *pchg = dev_get_drvdata(psy->dev.parent);
	u8 eoc_level;
	u8 ichg;
	u8 val;

	/* skip if no charger exists */
	if (!lp8727_is_charger_attached(psy->desc->name, pchg->devid))
		return;

	/* update charging parameters */
	if (pchg->chg_param) {
		eoc_level = pchg->chg_param->eoc_level;
		ichg = pchg->chg_param->ichg;
		val = (ichg << LP8727_ICHG_SHIFT) | eoc_level;
		lp8727_write_byte(pchg, LP8727_CHGCTRL2, val);
	}
}