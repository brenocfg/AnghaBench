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
struct nand_data_interface {int dummy; } ;
struct atmel_smc_cs_conf {int dummy; } ;
struct atmel_nand_cs {struct atmel_smc_cs_conf smcconf; int /*<<< orphan*/  id; } ;
struct atmel_nand_controller {int /*<<< orphan*/  smc; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct atmel_nand {struct atmel_nand_cs* cs; TYPE_1__ base; } ;

/* Variables and functions */
 int NAND_DATA_IFACE_CHECK_ONLY ; 
 int /*<<< orphan*/  atmel_smc_cs_conf_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct atmel_smc_cs_conf*) ; 
 int atmel_smc_nand_prepare_smcconf (struct atmel_nand*,struct nand_data_interface const*,struct atmel_smc_cs_conf*) ; 
 struct atmel_nand_controller* to_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_smc_nand_setup_data_interface(struct atmel_nand *nand,
					int csline,
					const struct nand_data_interface *conf)
{
	struct atmel_nand_controller *nc;
	struct atmel_smc_cs_conf smcconf;
	struct atmel_nand_cs *cs;
	int ret;

	nc = to_nand_controller(nand->base.controller);

	ret = atmel_smc_nand_prepare_smcconf(nand, conf, &smcconf);
	if (ret)
		return ret;

	if (csline == NAND_DATA_IFACE_CHECK_ONLY)
		return 0;

	cs = &nand->cs[csline];
	cs->smcconf = smcconf;
	atmel_smc_cs_conf_apply(nc->smc, cs->id, &cs->smcconf);

	return 0;
}