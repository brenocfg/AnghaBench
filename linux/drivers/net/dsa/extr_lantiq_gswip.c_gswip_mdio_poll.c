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
struct gswip_priv {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GSWIP_MDIO_CTRL ; 
 int GSWIP_MDIO_CTRL_BUSY ; 
 int gswip_mdio_r (struct gswip_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int gswip_mdio_poll(struct gswip_priv *priv)
{
	int cnt = 100;

	while (likely(cnt--)) {
		u32 ctrl = gswip_mdio_r(priv, GSWIP_MDIO_CTRL);

		if ((ctrl & GSWIP_MDIO_CTRL_BUSY) == 0)
			return 0;
		usleep_range(20, 40);
	}

	return -ETIMEDOUT;
}