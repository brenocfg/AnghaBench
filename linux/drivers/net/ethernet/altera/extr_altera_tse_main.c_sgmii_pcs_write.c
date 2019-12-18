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
struct altera_tse_private {int /*<<< orphan*/  mac_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  csrwr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mdio_phy0 ; 
 scalar_t__ tse_csroffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sgmii_pcs_write(struct altera_tse_private *priv, int regnum,
				u16 value)
{
	csrwr32(value, priv->mac_dev, tse_csroffs(mdio_phy0) + regnum * 4);
}