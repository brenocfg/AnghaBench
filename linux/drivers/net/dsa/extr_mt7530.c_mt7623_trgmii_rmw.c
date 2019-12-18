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
typedef  int /*<<< orphan*/  u32 ;
struct mt7530_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt7623_trgmii_read (struct mt7530_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7623_trgmii_write (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt7623_trgmii_rmw(struct mt7530_priv *priv, u32 reg,
		  u32 mask, u32 set)
{
	u32 val;

	val = mt7623_trgmii_read(priv, reg);
	val &= ~mask;
	val |= set;
	mt7623_trgmii_write(priv, reg, val);
}