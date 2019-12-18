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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int DB2K_ACQ_CONTROL_ADC_PACER_DISABLE ; 
 int DB2K_ACQ_CONTROL_SEQ_STOP_SCAN_LIST ; 
 scalar_t__ DB2K_REG_ACQ_CONTROL ; 
 scalar_t__ DB2K_REG_TRIG_CONTROL ; 
 int DB2K_TRIG_CONTROL_DISABLE ; 
 int DB2K_TRIG_CONTROL_TYPE_ANALOG ; 
 int DB2K_TRIG_CONTROL_TYPE_TTL ; 
 int /*<<< orphan*/  db2k_adc_stop_dma_transfer (struct comedi_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void db2k_adc_disarm(struct comedi_device *dev)
{
	/* Disable hardware triggers */
	udelay(2);
	writew(DB2K_TRIG_CONTROL_TYPE_ANALOG | DB2K_TRIG_CONTROL_DISABLE,
	       dev->mmio + DB2K_REG_TRIG_CONTROL);
	udelay(2);
	writew(DB2K_TRIG_CONTROL_TYPE_TTL | DB2K_TRIG_CONTROL_DISABLE,
	       dev->mmio + DB2K_REG_TRIG_CONTROL);

	/* Stop the scan list FIFO from loading the configuration pipe */
	udelay(2);
	writew(DB2K_ACQ_CONTROL_SEQ_STOP_SCAN_LIST,
	       dev->mmio + DB2K_REG_ACQ_CONTROL);

	/* Stop the pacer clock */
	udelay(2);
	writew(DB2K_ACQ_CONTROL_ADC_PACER_DISABLE,
	       dev->mmio + DB2K_REG_ACQ_CONTROL);

	/* Stop the input dma (abort channel 1) */
	db2k_adc_stop_dma_transfer(dev);
}