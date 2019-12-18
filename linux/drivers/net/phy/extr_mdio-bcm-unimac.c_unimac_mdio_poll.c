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
struct unimac_mdio_priv {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  unimac_mdio_busy (struct unimac_mdio_priv*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int unimac_mdio_poll(void *wait_func_data)
{
	struct unimac_mdio_priv *priv = wait_func_data;
	unsigned int timeout = 1000;

	do {
		if (!unimac_mdio_busy(priv))
			return 0;

		usleep_range(1000, 2000);
	} while (--timeout);

	return -ETIMEDOUT;
}