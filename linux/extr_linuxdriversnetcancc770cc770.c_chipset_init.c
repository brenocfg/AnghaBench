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
struct cc770_priv {int clkout; int cpu_interface; int bus_config; } ;
struct TYPE_2__ {int /*<<< orphan*/  config; int /*<<< orphan*/ * id; int /*<<< orphan*/ * data; int /*<<< orphan*/  ctrl1; int /*<<< orphan*/  ctrl0; } ;

/* Variables and functions */
 int CTRL_CCE ; 
 int CTRL_INI ; 
 int INTPND_RES ; 
 int INTPND_UNC ; 
 int MSGLST_RES ; 
 int MSGOBJ_FIRST ; 
 int MSGOBJ_LAST ; 
 int MSGVAL_RES ; 
 int NEWDAT_RES ; 
 int RMTPND_RES ; 
 int RXIE_RES ; 
 int TXIE_RES ; 
 int TXRQST_RES ; 
 int /*<<< orphan*/  bus_config ; 
 int /*<<< orphan*/  cc770_read_reg (struct cc770_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc770_write_reg (struct cc770_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clkout ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  cpu_interface ; 
 int /*<<< orphan*/ * global_mask_ext ; 
 int /*<<< orphan*/ * global_mask_std ; 
 int /*<<< orphan*/  interrupt ; 
 TYPE_1__* msgobj ; 
 int /*<<< orphan*/  status ; 

__attribute__((used)) static void chipset_init(struct cc770_priv *priv)
{
	int mo, id, data;

	/* Enable configuration and put chip in bus-off, disable interrupts */
	cc770_write_reg(priv, control, (CTRL_CCE | CTRL_INI));

	/* Set CLKOUT divider and slew rates */
	cc770_write_reg(priv, clkout, priv->clkout);

	/* Configure CPU interface / CLKOUT enable */
	cc770_write_reg(priv, cpu_interface, priv->cpu_interface);

	/* Set bus configuration  */
	cc770_write_reg(priv, bus_config, priv->bus_config);

	/* Clear interrupts */
	cc770_read_reg(priv, interrupt);

	/* Clear status register */
	cc770_write_reg(priv, status, 0);

	/* Clear and invalidate message objects */
	for (mo = MSGOBJ_FIRST; mo <= MSGOBJ_LAST; mo++) {
		cc770_write_reg(priv, msgobj[mo].ctrl0,
				INTPND_UNC | RXIE_RES |
				TXIE_RES | MSGVAL_RES);
		cc770_write_reg(priv, msgobj[mo].ctrl0,
				INTPND_RES | RXIE_RES |
				TXIE_RES | MSGVAL_RES);
		cc770_write_reg(priv, msgobj[mo].ctrl1,
				NEWDAT_RES | MSGLST_RES |
				TXRQST_RES | RMTPND_RES);
		for (data = 0; data < 8; data++)
			cc770_write_reg(priv, msgobj[mo].data[data], 0);
		for (id = 0; id < 4; id++)
			cc770_write_reg(priv, msgobj[mo].id[id], 0);
		cc770_write_reg(priv, msgobj[mo].config, 0);
	}

	/* Set all global ID masks to "don't care" */
	cc770_write_reg(priv, global_mask_std[0], 0);
	cc770_write_reg(priv, global_mask_std[1], 0);
	cc770_write_reg(priv, global_mask_ext[0], 0);
	cc770_write_reg(priv, global_mask_ext[1], 0);
	cc770_write_reg(priv, global_mask_ext[2], 0);
	cc770_write_reg(priv, global_mask_ext[3], 0);

}