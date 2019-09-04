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
struct tpm_chip {int dummy; } ;
struct pnp_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ iotype; int /*<<< orphan*/  map_size; int /*<<< orphan*/  map_base; int /*<<< orphan*/  mem_base; int /*<<< orphan*/  config_size; int /*<<< orphan*/  config_port; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data_regs; } ;

/* Variables and functions */
 scalar_t__ TPM_INF_IO_PORT ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct tpm_chip* pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_chip_unregister (struct tpm_chip*) ; 
 TYPE_1__ tpm_dev ; 

__attribute__((used)) static void tpm_inf_pnp_remove(struct pnp_dev *dev)
{
	struct tpm_chip *chip = pnp_get_drvdata(dev);

	tpm_chip_unregister(chip);

	if (tpm_dev.iotype == TPM_INF_IO_PORT) {
		release_region(tpm_dev.data_regs, tpm_dev.data_size);
		release_region(tpm_dev.config_port,
			       tpm_dev.config_size);
	} else {
		iounmap(tpm_dev.mem_base);
		release_mem_region(tpm_dev.map_base, tpm_dev.map_size);
	}
}