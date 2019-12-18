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
typedef  int u32 ;
struct meson_spifc {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  REG_SLAVE ; 
 int SLAVE_TRST_DONE ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int meson_spifc_wait_ready(struct meson_spifc *spifc)
{
	unsigned long deadline = jiffies + msecs_to_jiffies(5);
	u32 data;

	do {
		regmap_read(spifc->regmap, REG_SLAVE, &data);
		if (data & SLAVE_TRST_DONE)
			return 0;
		cond_resched();
	} while (!time_after(jiffies, deadline));

	return -ETIMEDOUT;
}