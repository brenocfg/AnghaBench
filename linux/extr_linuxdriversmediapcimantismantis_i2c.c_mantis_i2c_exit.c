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
struct mantis_pci {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_INT_I2CDONE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mantis_mask_ints (struct mantis_pci*,int /*<<< orphan*/ ) ; 

int mantis_i2c_exit(struct mantis_pci *mantis)
{
	dprintk(MANTIS_DEBUG, 1, "Disabling I2C interrupt");
	mantis_mask_ints(mantis, MANTIS_INT_I2CDONE);

	dprintk(MANTIS_DEBUG, 1, "Removing I2C adapter");
	i2c_del_adapter(&mantis->adapter);

	return 0;
}