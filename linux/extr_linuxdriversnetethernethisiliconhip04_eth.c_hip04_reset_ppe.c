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
struct hip04_priv {int port; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 scalar_t__ PPE_CFG_RX_ADDR ; 
 scalar_t__ PPE_CURR_BUF_CNT ; 
 scalar_t__ RESET_TIMEOUT ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static void hip04_reset_ppe(struct hip04_priv *priv)
{
	u32 val, tmp, timeout = 0;

	do {
		regmap_read(priv->map, priv->port * 4 + PPE_CURR_BUF_CNT, &val);
		regmap_read(priv->map, priv->port * 4 + PPE_CFG_RX_ADDR, &tmp);
		if (timeout++ > RESET_TIMEOUT)
			break;
	} while (val & 0xfff);
}