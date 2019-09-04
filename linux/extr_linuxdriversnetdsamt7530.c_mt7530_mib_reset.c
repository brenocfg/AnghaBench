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
struct mt7530_priv {int dummy; } ;
struct dsa_switch {struct mt7530_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR_MIB_ACTIVATE ; 
 int /*<<< orphan*/  CCR_MIB_FLUSH ; 
 int /*<<< orphan*/  MT7530_MIB_CCR ; 
 int /*<<< orphan*/  mt7530_write (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt7530_mib_reset(struct dsa_switch *ds)
{
	struct mt7530_priv *priv = ds->priv;

	mt7530_write(priv, MT7530_MIB_CCR, CCR_MIB_FLUSH);
	mt7530_write(priv, MT7530_MIB_CCR, CCR_MIB_ACTIVATE);
}