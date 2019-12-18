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
struct ir_raw_event {int carrier_report; int carrier; int duty_cycle; } ;
struct ene_device {int /*<<< orphan*/  rdev; scalar_t__ carrier_detect_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENE_CIRCAR_HPRD ; 
 int /*<<< orphan*/  ENE_CIRCAR_PRD ; 
 int ENE_CIRCAR_PRD_VALID ; 
 int /*<<< orphan*/  dbg (char*,int,...) ; 
 int ene_read_reg (struct ene_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_store (int /*<<< orphan*/ ,struct ir_raw_event*) ; 

__attribute__((used)) static void ene_rx_sense_carrier(struct ene_device *dev)
{
	int carrier, duty_cycle;
	int period = ene_read_reg(dev, ENE_CIRCAR_PRD);
	int hperiod = ene_read_reg(dev, ENE_CIRCAR_HPRD);

	if (!(period & ENE_CIRCAR_PRD_VALID))
		return;

	period &= ~ENE_CIRCAR_PRD_VALID;

	if (!period)
		return;

	dbg("RX: hardware carrier period = %02x", period);
	dbg("RX: hardware carrier pulse period = %02x", hperiod);

	carrier = 2000000 / period;
	duty_cycle = (hperiod * 100) / period;
	dbg("RX: sensed carrier = %d Hz, duty cycle %d%%",
						carrier, duty_cycle);
	if (dev->carrier_detect_enabled) {
		struct ir_raw_event ev = {
			.carrier_report = true,
			.carrier = carrier,
			.duty_cycle = duty_cycle
		};
		ir_raw_event_store(dev->rdev, &ev);
	}
}