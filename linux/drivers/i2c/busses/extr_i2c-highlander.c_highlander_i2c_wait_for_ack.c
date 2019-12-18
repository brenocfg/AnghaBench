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
typedef  int u16 ;
struct highlander_i2c_dev {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SMCR ; 
 int SMCR_ACKE ; 
 int SMCR_IRIC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int highlander_i2c_reset (struct highlander_i2c_dev*) ; 
 int ioread16 (scalar_t__) ; 

__attribute__((used)) static int highlander_i2c_wait_for_ack(struct highlander_i2c_dev *dev)
{
	u16 tmp = ioread16(dev->base + SMCR);

	if ((tmp & (SMCR_IRIC | SMCR_ACKE)) == SMCR_ACKE) {
		dev_warn(dev->dev, "ack abnormality\n");
		return highlander_i2c_reset(dev);
	}

	return 0;
}