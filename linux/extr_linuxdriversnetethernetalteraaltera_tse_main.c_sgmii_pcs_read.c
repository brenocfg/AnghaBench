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
typedef  int u16 ;
struct altera_tse_private {int /*<<< orphan*/  mac_dev; } ;

/* Variables and functions */
 int csrrd32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mdio_phy0 ; 
 scalar_t__ tse_csroffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 sgmii_pcs_read(struct altera_tse_private *priv, int regnum)
{
	return csrrd32(priv->mac_dev,
		       tse_csroffs(mdio_phy0) + regnum * 4) & 0xffff;
}