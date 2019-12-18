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
struct nand_ecc_step_info {int stepsize; int nstrengths; int* strengths; } ;
struct nand_ecc_caps {int nstepinfos; int (* calc_ecc_bytes ) (int,int) ;struct nand_ecc_step_info* stepinfos; } ;
struct TYPE_2__ {int size; int strength; int bytes; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int stub1 (int,int) ; 

__attribute__((used)) static int
nand_maximize_ecc(struct nand_chip *chip,
		  const struct nand_ecc_caps *caps, int oobavail)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	const struct nand_ecc_step_info *stepinfo;
	int step_size, strength, nsteps, ecc_bytes, corr;
	int best_corr = 0;
	int best_step = 0;
	int best_strength, best_ecc_bytes;
	int i, j;

	for (i = 0; i < caps->nstepinfos; i++) {
		stepinfo = &caps->stepinfos[i];
		step_size = stepinfo->stepsize;

		/* If chip->ecc.size is already set, respect it */
		if (chip->ecc.size && step_size != chip->ecc.size)
			continue;

		for (j = 0; j < stepinfo->nstrengths; j++) {
			strength = stepinfo->strengths[j];

			if (mtd->writesize % step_size)
				continue;

			nsteps = mtd->writesize / step_size;

			ecc_bytes = caps->calc_ecc_bytes(step_size, strength);
			if (WARN_ON_ONCE(ecc_bytes < 0))
				continue;

			if (ecc_bytes * nsteps > oobavail)
				continue;

			corr = strength * nsteps;

			/*
			 * If the number of correctable bits is the same,
			 * bigger step_size has more reliability.
			 */
			if (corr > best_corr ||
			    (corr == best_corr && step_size > best_step)) {
				best_corr = corr;
				best_step = step_size;
				best_strength = strength;
				best_ecc_bytes = ecc_bytes;
			}
		}
	}

	if (!best_corr)
		return -ENOTSUPP;

	chip->ecc.size = best_step;
	chip->ecc.strength = best_strength;
	chip->ecc.bytes = best_ecc_bytes;

	return 0;
}