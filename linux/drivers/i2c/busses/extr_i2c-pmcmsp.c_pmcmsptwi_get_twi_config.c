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
struct pmcmsptwi_data {int /*<<< orphan*/  lock; scalar_t__ iobase; } ;
struct pmcmsptwi_cfg {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSP_TWI_CFG_REG_OFFSET ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcmsptwi_readl (scalar_t__) ; 
 int /*<<< orphan*/  pmcmsptwi_reg_to_cfg (int /*<<< orphan*/ ,struct pmcmsptwi_cfg*) ; 

__attribute__((used)) static void pmcmsptwi_get_twi_config(struct pmcmsptwi_cfg *cfg,
					struct pmcmsptwi_data *data)
{
	mutex_lock(&data->lock);
	pmcmsptwi_reg_to_cfg(pmcmsptwi_readl(
				data->iobase + MSP_TWI_CFG_REG_OFFSET), cfg);
	mutex_unlock(&data->lock);
}