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
struct TYPE_6__ {int options; int steps; } ;
struct TYPE_4__ {int strength; } ;
struct TYPE_5__ {TYPE_1__ eccreq; } ;
struct nand_chip {TYPE_3__ ecc; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_BYTE ; 
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int NAND_ECC_MAXIMIZE ; 
 int SKIP_SPARE_BYTES ; 
 int round_up (int,int) ; 

__attribute__((used)) static int tegra_nand_get_strength(struct nand_chip *chip, const int *strength,
				   int strength_len, int bits_per_step,
				   int oobsize)
{
	bool maximize = chip->ecc.options & NAND_ECC_MAXIMIZE;
	int i;

	/*
	 * Loop through available strengths. Backwards in case we try to
	 * maximize the BCH strength.
	 */
	for (i = 0; i < strength_len; i++) {
		int strength_sel, bytes_per_step, bytes_per_page;

		if (maximize) {
			strength_sel = strength[strength_len - i - 1];
		} else {
			strength_sel = strength[i];

			if (strength_sel < chip->base.eccreq.strength)
				continue;
		}

		bytes_per_step = DIV_ROUND_UP(bits_per_step * strength_sel,
					      BITS_PER_BYTE);
		bytes_per_page = round_up(bytes_per_step * chip->ecc.steps, 4);

		/* Check whether strength fits OOB */
		if (bytes_per_page < (oobsize - SKIP_SPARE_BYTES))
			return strength_sel;
	}

	return -EINVAL;
}