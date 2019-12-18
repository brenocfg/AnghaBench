#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct s3c2410_nand_mtd {TYPE_2__* set; struct s3c2410_nand_info* info; } ;
struct s3c2410_nand_info {unsigned long sel_bit; int /*<<< orphan*/  sel_reg; TYPE_1__* platform; int /*<<< orphan*/  device; } ;
struct nand_chip {int dummy; } ;
struct TYPE_4__ {int nr_chips; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* select_chip ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_ENABLE ; 
 int /*<<< orphan*/  CLOCK_SUSPEND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct s3c2410_nand_mtd* nand_get_controller_data (struct nand_chip*) ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_nand_clk_set_state (struct s3c2410_nand_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c2410_nand_select_chip(struct nand_chip *this, int chip)
{
	struct s3c2410_nand_info *info;
	struct s3c2410_nand_mtd *nmtd;
	unsigned long cur;

	nmtd = nand_get_controller_data(this);
	info = nmtd->info;

	if (chip != -1)
		s3c2410_nand_clk_set_state(info, CLOCK_ENABLE);

	cur = readl(info->sel_reg);

	if (chip == -1) {
		cur |= info->sel_bit;
	} else {
		if (nmtd->set != NULL && chip > nmtd->set->nr_chips) {
			dev_err(info->device, "invalid chip %d\n", chip);
			return;
		}

		if (info->platform != NULL) {
			if (info->platform->select_chip != NULL)
				(info->platform->select_chip) (nmtd->set, chip);
		}

		cur &= ~info->sel_bit;
	}

	writel(cur, info->sel_reg);

	if (chip == -1)
		s3c2410_nand_clk_set_state(info, CLOCK_SUSPEND);
}