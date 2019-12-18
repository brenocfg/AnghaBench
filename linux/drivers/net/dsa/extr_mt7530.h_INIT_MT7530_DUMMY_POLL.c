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
struct mt7530_dummy_poll {int /*<<< orphan*/  reg; struct mt7530_priv* priv; } ;

/* Variables and functions */

__attribute__((used)) static inline void INIT_MT7530_DUMMY_POLL(struct mt7530_dummy_poll *p,
					  struct mt7530_priv *priv, u32 reg)
{
	p->priv = priv;
	p->reg = reg;
}