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
struct wbcir_data {scalar_t__ ebase; scalar_t__ pulse_duration; int /*<<< orphan*/  dev; } ;
struct ir_raw_event {int carrier_report; int /*<<< orphan*/  carrier; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (unsigned int,scalar_t__) ; 
 int WBCIR_CNTR_EN ; 
 int WBCIR_CNTR_R ; 
 scalar_t__ WBCIR_REG_ECEIR_CCTL ; 
 scalar_t__ WBCIR_REG_ECEIR_CNT_HI ; 
 scalar_t__ WBCIR_REG_ECEIR_CNT_LO ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  ir_raw_event_store (int /*<<< orphan*/ ,struct ir_raw_event*) ; 
 int /*<<< orphan*/  wbcir_set_bits (scalar_t__,int,int) ; 

__attribute__((used)) static void
wbcir_carrier_report(struct wbcir_data *data)
{
	unsigned counter = inb(data->ebase + WBCIR_REG_ECEIR_CNT_LO) |
			inb(data->ebase + WBCIR_REG_ECEIR_CNT_HI) << 8;

	if (counter > 0 && counter < 0xffff) {
		struct ir_raw_event ev = {
			.carrier_report = 1,
			.carrier = DIV_ROUND_CLOSEST(counter * 1000000u,
						data->pulse_duration)
		};

		ir_raw_event_store(data->dev, &ev);
	}

	/* reset and restart the counter */
	data->pulse_duration = 0;
	wbcir_set_bits(data->ebase + WBCIR_REG_ECEIR_CCTL, WBCIR_CNTR_R,
						WBCIR_CNTR_EN | WBCIR_CNTR_R);
	wbcir_set_bits(data->ebase + WBCIR_REG_ECEIR_CCTL, WBCIR_CNTR_EN,
						WBCIR_CNTR_EN | WBCIR_CNTR_R);
}