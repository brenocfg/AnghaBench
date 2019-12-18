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
struct regmap {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  REG_IND_AP ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ time_before_eq (int,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int write_ind_ap(struct regmap *regmap, unsigned int ind_ap)
{
	unsigned long timeout = jiffies + HZ / 2;
	unsigned int v, i = 0;

	while (time_before_eq(jiffies, timeout)) {
		regmap_write(regmap, REG_IND_AP, ind_ap);
		regmap_read(regmap, REG_IND_AP, &v);
		if (likely(ind_ap == v))
			return 0;
		if (i < 10) {
			cpu_relax();
			i++;
		} else {
			usleep_range(500, 1000);
		}
	}
	WARN(1, "IND_AP register not stable");
	return -ETIMEDOUT;
}