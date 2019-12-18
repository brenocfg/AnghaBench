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
typedef  int /*<<< orphan*/  u16 ;
struct w5300_priv {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  W5300_S0_CR ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ w5300_read (struct w5300_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w5300_write (struct w5300_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w5300_command(struct w5300_priv *priv, u16 cmd)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(100);

	w5300_write(priv, W5300_S0_CR, cmd);

	while (w5300_read(priv, W5300_S0_CR) != 0) {
		if (time_after(jiffies, timeout))
			return -EIO;
		cpu_relax();
	}

	return 0;
}