#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rv3028_data {TYPE_2__* rtc; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_1__ attr; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {TYPE_3__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_PF ; 
 unsigned long RTC_UF ; 
 int /*<<< orphan*/  RV3028_CTRL2 ; 
 int RV3028_CTRL2_AIE ; 
 int RV3028_CTRL2_TIE ; 
 int RV3028_CTRL2_UIE ; 
 int /*<<< orphan*/  RV3028_STATUS ; 
 int RV3028_STATUS_AF ; 
 int RV3028_STATUS_EVF ; 
 int RV3028_STATUS_PORF ; 
 int RV3028_STATUS_TF ; 
 int RV3028_STATUS_UF ; 
 TYPE_4__ dev_attr_timestamp0 ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 scalar_t__ regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (TYPE_2__*,int,unsigned long) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rv3028_handle_irq(int irq, void *dev_id)
{
	struct rv3028_data *rv3028 = dev_id;
	unsigned long events = 0;
	u32 status = 0, ctrl = 0;

	if (regmap_read(rv3028->regmap, RV3028_STATUS, &status) < 0 ||
	   status == 0) {
		return IRQ_NONE;
	}

	if (status & RV3028_STATUS_PORF)
		dev_warn(&rv3028->rtc->dev, "Voltage low, data loss detected.\n");

	if (status & RV3028_STATUS_TF) {
		status |= RV3028_STATUS_TF;
		ctrl |= RV3028_CTRL2_TIE;
		events |= RTC_PF;
	}

	if (status & RV3028_STATUS_AF) {
		status |= RV3028_STATUS_AF;
		ctrl |= RV3028_CTRL2_AIE;
		events |= RTC_AF;
	}

	if (status & RV3028_STATUS_UF) {
		status |= RV3028_STATUS_UF;
		ctrl |= RV3028_CTRL2_UIE;
		events |= RTC_UF;
	}

	if (events) {
		rtc_update_irq(rv3028->rtc, 1, events);
		regmap_update_bits(rv3028->regmap, RV3028_STATUS, status, 0);
		regmap_update_bits(rv3028->regmap, RV3028_CTRL2, ctrl, 0);
	}

	if (status & RV3028_STATUS_EVF) {
		sysfs_notify(&rv3028->rtc->dev.kobj, NULL,
			     dev_attr_timestamp0.attr.name);
		dev_warn(&rv3028->rtc->dev, "event detected");
	}

	return IRQ_HANDLED;
}