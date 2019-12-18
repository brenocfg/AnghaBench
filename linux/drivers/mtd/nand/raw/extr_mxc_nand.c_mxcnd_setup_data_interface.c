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
struct nand_chip {int dummy; } ;
struct mxc_nand_host {TYPE_1__* devtype_data; } ;
struct TYPE_2__ {int (* setup_data_interface ) (struct nand_chip*,int,struct nand_data_interface const*) ;} ;

/* Variables and functions */
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int stub1 (struct nand_chip*,int,struct nand_data_interface const*) ; 

__attribute__((used)) static int mxcnd_setup_data_interface(struct nand_chip *chip, int chipnr,
				      const struct nand_data_interface *conf)
{
	struct mxc_nand_host *host = nand_get_controller_data(chip);

	return host->devtype_data->setup_data_interface(chip, chipnr, conf);
}