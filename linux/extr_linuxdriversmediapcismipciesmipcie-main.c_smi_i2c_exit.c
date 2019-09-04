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
struct smi_dev {int /*<<< orphan*/ * i2c_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smi_i2c_exit(struct smi_dev *dev)
{
	i2c_del_adapter(&dev->i2c_bus[0]);
	i2c_del_adapter(&dev->i2c_bus[1]);
}