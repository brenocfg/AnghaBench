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
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBUS_TARG_PRPH_WADDR ; 
 int /*<<< orphan*/  HBUS_TARG_PRPH_WDAT ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
_il_wr_prph(struct il_priv *il, u32 addr, u32 val)
{
	_il_wr(il, HBUS_TARG_PRPH_WADDR, ((addr & 0x0000FFFF) | (3 << 24)));
	_il_wr(il, HBUS_TARG_PRPH_WDAT, val);
}