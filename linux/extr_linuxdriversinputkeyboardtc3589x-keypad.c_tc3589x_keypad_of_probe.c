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
typedef  void* u8 ;
typedef  int u32 ;
typedef  struct tc3589x_keypad_platform_data {scalar_t__ kcol; scalar_t__ krow; int enable_wakeup; int debounce_period; int /*<<< orphan*/  irqtype; int /*<<< orphan*/  settle_time; scalar_t__ no_autorepeat; } const tc3589x_keypad_platform_data ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct tc3589x_keypad_platform_data const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 scalar_t__ TC_KPD_COLUMNS ; 
 int TC_KPD_DEBOUNCE_PERIOD ; 
 scalar_t__ TC_KPD_ROWS ; 
 int /*<<< orphan*/  TC_KPD_SETTLE_TIME ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct tc3589x_keypad_platform_data const* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_property (struct device_node*,char*,int*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static const struct tc3589x_keypad_platform_data *
tc3589x_keypad_of_probe(struct device *dev)
{
	struct device_node *np = dev->of_node;
	struct tc3589x_keypad_platform_data *plat;
	u32 cols, rows;
	u32 debounce_ms;
	int proplen;

	if (!np)
		return ERR_PTR(-ENODEV);

	plat = devm_kzalloc(dev, sizeof(*plat), GFP_KERNEL);
	if (!plat)
		return ERR_PTR(-ENOMEM);

	of_property_read_u32(np, "keypad,num-columns", &cols);
	of_property_read_u32(np, "keypad,num-rows", &rows);
	plat->kcol = (u8) cols;
	plat->krow = (u8) rows;
	if (!plat->krow || !plat->kcol ||
	     plat->krow > TC_KPD_ROWS || plat->kcol > TC_KPD_COLUMNS) {
		dev_err(dev,
			"keypad columns/rows not properly specified (%ux%u)\n",
			plat->kcol, plat->krow);
		return ERR_PTR(-EINVAL);
	}

	if (!of_get_property(np, "linux,keymap", &proplen)) {
		dev_err(dev, "property linux,keymap not found\n");
		return ERR_PTR(-ENOENT);
	}

	plat->no_autorepeat = of_property_read_bool(np, "linux,no-autorepeat");

	plat->enable_wakeup = of_property_read_bool(np, "wakeup-source") ||
			      /* legacy name */
			      of_property_read_bool(np, "linux,wakeup");

	/* The custom delay format is ms/16 */
	of_property_read_u32(np, "debounce-delay-ms", &debounce_ms);
	if (debounce_ms)
		plat->debounce_period = debounce_ms * 16;
	else
		plat->debounce_period = TC_KPD_DEBOUNCE_PERIOD;

	plat->settle_time = TC_KPD_SETTLE_TIME;
	/* FIXME: should be property of the IRQ resource? */
	plat->irqtype = IRQF_TRIGGER_FALLING;

	return plat;
}