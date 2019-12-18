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
struct nand_sdr_timings {int /*<<< orphan*/  tR_max; } ;
struct nand_chip {int options; int /*<<< orphan*/  data_interface; } ;

/* Variables and functions */
 int NAND_NEED_READRDY ; 
 int /*<<< orphan*/  PSEC_TO_MSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_wait_rdy_op (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nand_wait_readrdy(struct nand_chip *chip)
{
	const struct nand_sdr_timings *sdr;

	if (!(chip->options & NAND_NEED_READRDY))
		return;

	sdr = nand_get_sdr_timings(&chip->data_interface);
	WARN_ON(nand_wait_rdy_op(chip, PSEC_TO_MSEC(sdr->tR_max), 0));
}