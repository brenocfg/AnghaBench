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
struct nand_sdr_timings {int tRC_min; } ;
struct nand_data_interface {int dummy; } ;
struct nand_chip {int dummy; } ;
struct TYPE_2__ {int must_apply_timings; } ;
struct gpmi_nand_data {TYPE_1__ hw; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  GPMI_IS_MX6 (struct gpmi_nand_data*) ; 
 scalar_t__ IS_ERR (struct nand_sdr_timings const*) ; 
 int PTR_ERR (struct nand_sdr_timings const*) ; 
 int /*<<< orphan*/  gpmi_nfc_compute_timings (struct gpmi_nand_data*,struct nand_sdr_timings const*) ; 
 struct gpmi_nand_data* nand_get_controller_data (struct nand_chip*) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (struct nand_data_interface const*) ; 

__attribute__((used)) static int gpmi_setup_data_interface(struct nand_chip *chip, int chipnr,
				     const struct nand_data_interface *conf)
{
	struct gpmi_nand_data *this = nand_get_controller_data(chip);
	const struct nand_sdr_timings *sdr;

	/* Retrieve required NAND timings */
	sdr = nand_get_sdr_timings(conf);
	if (IS_ERR(sdr))
		return PTR_ERR(sdr);

	/* Only MX6 GPMI controller can reach EDO timings */
	if (sdr->tRC_min <= 25000 && !GPMI_IS_MX6(this))
		return -ENOTSUPP;

	/* Stop here if this call was just a check */
	if (chipnr < 0)
		return 0;

	/* Do the actual derivation of the controller timings */
	gpmi_nfc_compute_timings(this, sdr);

	this->hw.must_apply_timings = true;

	return 0;
}