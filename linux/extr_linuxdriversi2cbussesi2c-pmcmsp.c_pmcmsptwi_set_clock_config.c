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
struct pmcmsptwi_clockcfg {int /*<<< orphan*/  highspeed; int /*<<< orphan*/  standard; } ;

/* Variables and functions */
 scalar_t__ MSP_TWI_HS_CLK_REG_OFFSET ; 
 scalar_t__ MSP_TWI_SF_CLK_REG_OFFSET ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcmsptwi_clock_to_reg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcmsptwi_writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pmcmsptwi_set_clock_config(const struct pmcmsptwi_clockcfg *cfg,
					struct pmcmsptwi_data *data)
{
	mutex_lock(&data->lock);
	pmcmsptwi_writel(pmcmsptwi_clock_to_reg(&cfg->standard),
				data->iobase + MSP_TWI_SF_CLK_REG_OFFSET);
	pmcmsptwi_writel(pmcmsptwi_clock_to_reg(&cfg->highspeed),
				data->iobase + MSP_TWI_HS_CLK_REG_OFFSET);
	mutex_unlock(&data->lock);
}