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
typedef  int /*<<< orphan*/  u8 ;
struct dt9812_private {int /*<<< orphan*/  mut; } ;
struct comedi_device {struct dt9812_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  F020_SFR_P2 ; 
 int dt9812_write_multiple_registers (struct comedi_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dt9812_digital_out(struct comedi_device *dev, u8 bits)
{
	struct dt9812_private *devpriv = dev->private;
	u8 reg[1] = { F020_SFR_P2 };
	u8 value[1] = { bits };
	int ret;

	mutex_lock(&devpriv->mut);
	ret = dt9812_write_multiple_registers(dev, 1, reg, value);
	mutex_unlock(&devpriv->mut);

	return ret;
}