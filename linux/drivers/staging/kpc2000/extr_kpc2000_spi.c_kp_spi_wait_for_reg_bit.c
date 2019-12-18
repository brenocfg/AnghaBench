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
struct kp_spi_controller_state {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 unsigned long kp_spi_read_reg (struct kp_spi_controller_state*,int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int
kp_spi_wait_for_reg_bit(struct kp_spi_controller_state *cs, int idx,
			unsigned long bit)
{
	unsigned long timeout;

	timeout = jiffies + msecs_to_jiffies(1000);
	while (!(kp_spi_read_reg(cs, idx) & bit)) {
		if (time_after(jiffies, timeout)) {
			if (!(kp_spi_read_reg(cs, idx) & bit))
				return -ETIMEDOUT;
			else
				return 0;
		}
		cpu_relax();
	}
	return 0;
}