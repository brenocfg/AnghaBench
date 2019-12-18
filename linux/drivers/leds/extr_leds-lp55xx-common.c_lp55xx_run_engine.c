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
struct lp55xx_chip {TYPE_1__* cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* run_engine ) (struct lp55xx_chip*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct lp55xx_chip*,int) ; 

__attribute__((used)) static inline void lp55xx_run_engine(struct lp55xx_chip *chip, bool start)
{
	if (chip->cfg->run_engine)
		chip->cfg->run_engine(chip, start);
}