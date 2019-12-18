#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct isci_host {TYPE_3__* scu_registers; } ;
struct TYPE_4__ {int /*<<< orphan*/ * output_data_select; } ;
struct TYPE_5__ {TYPE_1__ sgpio; } ;
struct TYPE_6__ {TYPE_2__ peg0; } ;

/* Variables and functions */
 int EINVAL ; 
 int isci_gpio_count (struct isci_host*) ; 
 int /*<<< orphan*/  to_sas_gpio_od (int,int) ; 
 int try_test_sas_gpio_gp_bit (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sci_write_gpio_tx_gp(struct isci_host *ihost, u8 reg_index, u8 reg_count, u8 *write_data)
{
	int d;

	/* no support for TX_GP_CFG */
	if (reg_index == 0)
		return -EINVAL;

	for (d = 0; d < isci_gpio_count(ihost); d++) {
		u32 val = 0x444; /* all ODx.n clear */
		int i;

		for (i = 0; i < 3; i++) {
			int bit;

			bit = try_test_sas_gpio_gp_bit(to_sas_gpio_od(d, i),
						       write_data, reg_index,
						       reg_count);
			if (bit < 0)
				break;

			/* if od is set, clear the 'invert' bit */
			val &= ~(bit << ((i << 2) + 2));
		}

		if (i < 3)
			break;
		writel(val, &ihost->scu_registers->peg0.sgpio.output_data_select[d]);
	}

	/* unless reg_index is > 1, we should always be able to write at
	 * least one register
	 */
	return d > 0;
}