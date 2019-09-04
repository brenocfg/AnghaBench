#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpr0521_data {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int RPR0521_INTERRUPT_INT_REASSERT_DISABLE ; 
 int RPR0521_INTERRUPT_INT_TRIG_ALS_DISABLE ; 
 int RPR0521_INTERRUPT_INT_TRIG_PS_ENABLE ; 
 int /*<<< orphan*/  RPR0521_PXS_PERSISTENCE_DRDY ; 
 int /*<<< orphan*/  RPR0521_PXS_PERSISTENCE_MASK ; 
 int /*<<< orphan*/  RPR0521_REG_INTERRUPT ; 
 int /*<<< orphan*/  RPR0521_REG_PXS_CTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rpr0521_write_int_enable(struct rpr0521_data *data)
{
	int err;

	/* Interrupt after each measurement */
	err = regmap_update_bits(data->regmap, RPR0521_REG_PXS_CTRL,
		RPR0521_PXS_PERSISTENCE_MASK,
		RPR0521_PXS_PERSISTENCE_DRDY);
	if (err) {
		dev_err(&data->client->dev, "PS control reg write fail.\n");
		return -EBUSY;
		}

	/* Ignore latch and mode because of drdy */
	err = regmap_write(data->regmap, RPR0521_REG_INTERRUPT,
		RPR0521_INTERRUPT_INT_REASSERT_DISABLE |
		RPR0521_INTERRUPT_INT_TRIG_ALS_DISABLE |
		RPR0521_INTERRUPT_INT_TRIG_PS_ENABLE
		);
	if (err) {
		dev_err(&data->client->dev, "Interrupt setup write fail.\n");
		return -EBUSY;
		}

	return 0;
}