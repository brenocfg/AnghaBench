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
struct labpc_private {int /*<<< orphan*/  (* write_byte ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;} ;
struct comedi_device {struct labpc_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_FIFO_CLEAR_REG ; 
 int /*<<< orphan*/  labpc_read_adc_fifo (struct comedi_device*) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void labpc_clear_adc_fifo(struct comedi_device *dev)
{
	struct labpc_private *devpriv = dev->private;

	devpriv->write_byte(dev, 0x1, ADC_FIFO_CLEAR_REG);
	labpc_read_adc_fifo(dev);
}