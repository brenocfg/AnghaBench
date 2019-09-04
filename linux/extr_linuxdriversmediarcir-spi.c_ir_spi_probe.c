#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_2__ dev; } ;
struct ir_spi_data {TYPE_1__* rc; int /*<<< orphan*/  freq; int /*<<< orphan*/  negated; struct spi_device* spi; int /*<<< orphan*/  regulator; } ;
struct TYPE_8__ {char* device_name; struct ir_spi_data* priv; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  (* s_tx_duty_cycle ) (TYPE_1__*,int) ;int /*<<< orphan*/  s_tx_carrier; int /*<<< orphan*/  tx_ir; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IR_SPI_DEFAULT_FREQUENCY ; 
 int /*<<< orphan*/  IR_SPI_DRIVER_NAME ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW_TX ; 
 struct ir_spi_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_rc_allocate_device (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int devm_rc_register_device (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ir_spi_set_duty_cycle (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ir_spi_set_tx_carrier ; 
 int /*<<< orphan*/  ir_spi_tx ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_u8 (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int ir_spi_probe(struct spi_device *spi)
{
	int ret;
	u8 dc;
	struct ir_spi_data *idata;

	idata = devm_kzalloc(&spi->dev, sizeof(*idata), GFP_KERNEL);
	if (!idata)
		return -ENOMEM;

	idata->regulator = devm_regulator_get(&spi->dev, "irda_regulator");
	if (IS_ERR(idata->regulator))
		return PTR_ERR(idata->regulator);

	idata->rc = devm_rc_allocate_device(&spi->dev, RC_DRIVER_IR_RAW_TX);
	if (!idata->rc)
		return -ENOMEM;

	idata->rc->tx_ir           = ir_spi_tx;
	idata->rc->s_tx_carrier    = ir_spi_set_tx_carrier;
	idata->rc->s_tx_duty_cycle = ir_spi_set_duty_cycle;
	idata->rc->device_name	   = "IR SPI";
	idata->rc->driver_name     = IR_SPI_DRIVER_NAME;
	idata->rc->priv            = idata;
	idata->spi                 = spi;

	idata->negated = of_property_read_bool(spi->dev.of_node,
							"led-active-low");
	ret = of_property_read_u8(spi->dev.of_node, "duty-cycle", &dc);
	if (ret)
		dc = 50;

	/* ir_spi_set_duty_cycle cannot fail,
	 * it returns int to be compatible with the
	 * rc->s_tx_duty_cycle function
	 */
	ir_spi_set_duty_cycle(idata->rc, dc);

	idata->freq = IR_SPI_DEFAULT_FREQUENCY;

	return devm_rc_register_device(&spi->dev, idata->rc);
}