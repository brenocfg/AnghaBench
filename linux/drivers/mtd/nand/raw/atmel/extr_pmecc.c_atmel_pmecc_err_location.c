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
typedef  int u32 ;
struct atmel_pmecc_user {int* lmu; int /*<<< orphan*/ * smu; struct atmel_pmecc* pmecc; } ;
struct TYPE_2__ {scalar_t__ errloc; } ;
struct atmel_pmecc {int /*<<< orphan*/  dev; TYPE_1__ regs; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 scalar_t__ ATMEL_PMERRLOC_ELCFG ; 
 scalar_t__ ATMEL_PMERRLOC_ELDIS ; 
 scalar_t__ ATMEL_PMERRLOC_ELEN ; 
 scalar_t__ ATMEL_PMERRLOC_ELISR ; 
 scalar_t__ ATMEL_PMERRLOC_SIGMA (int) ; 
 int EBADMSG ; 
 int PMECC_MAX_TIMEOUT_MS ; 
 int PMERRLOC_CALC_DONE ; 
 int PMERRLOC_DISABLE ; 
 int PMERRLOC_ERR_NUM_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int get_sectorsize (struct atmel_pmecc_user*) ; 
 int get_strength (struct atmel_pmecc_user*) ; 
 int readl_relaxed_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int atmel_pmecc_err_location(struct atmel_pmecc_user *user)
{
	int sector_size = get_sectorsize(user);
	int degree = sector_size == 512 ? 13 : 14;
	struct atmel_pmecc *pmecc = user->pmecc;
	int strength = get_strength(user);
	int ret, roots_nbr, i, err_nbr = 0;
	int num = (2 * strength) + 1;
	s16 *smu = user->smu;
	u32 val;

	writel(PMERRLOC_DISABLE, pmecc->regs.errloc + ATMEL_PMERRLOC_ELDIS);

	for (i = 0; i <= user->lmu[strength + 1] >> 1; i++) {
		writel_relaxed(smu[(strength + 1) * num + i],
			       pmecc->regs.errloc + ATMEL_PMERRLOC_SIGMA(i));
		err_nbr++;
	}

	val = (err_nbr - 1) << 16;
	if (sector_size == 1024)
		val |= 1;

	writel(val, pmecc->regs.errloc + ATMEL_PMERRLOC_ELCFG);
	writel((sector_size * 8) + (degree * strength),
	       pmecc->regs.errloc + ATMEL_PMERRLOC_ELEN);

	ret = readl_relaxed_poll_timeout(pmecc->regs.errloc +
					 ATMEL_PMERRLOC_ELISR,
					 val, val & PMERRLOC_CALC_DONE, 0,
					 PMECC_MAX_TIMEOUT_MS * 1000);
	if (ret) {
		dev_err(pmecc->dev,
			"PMECC: Timeout to calculate error location.\n");
		return ret;
	}

	roots_nbr = (val & PMERRLOC_ERR_NUM_MASK) >> 8;
	/* Number of roots == degree of smu hence <= cap */
	if (roots_nbr == user->lmu[strength + 1] >> 1)
		return err_nbr - 1;

	/*
	 * Number of roots does not match the degree of smu
	 * unable to correct error.
	 */
	return -EBADMSG;
}