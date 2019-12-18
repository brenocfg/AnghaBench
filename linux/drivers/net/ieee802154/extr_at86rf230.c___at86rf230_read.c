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
struct at86rf230_local {int sleep; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  at86rf230_awake (struct at86rf230_local*) ; 
 int /*<<< orphan*/  at86rf230_sleep (struct at86rf230_local*) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static inline int
__at86rf230_read(struct at86rf230_local *lp,
		 unsigned int addr, unsigned int *data)
{
	bool sleep = lp->sleep;
	int ret;

	/* awake for register setting if sleep */
	if (sleep)
		at86rf230_awake(lp);

	ret = regmap_read(lp->regmap, addr, data);

	/* sleep again if was sleeping */
	if (sleep)
		at86rf230_sleep(lp);

	return ret;
}