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
 int /*<<< orphan*/  HBUS_TARG_PRPH_RADDR ; 
 int /*<<< orphan*/  HBUS_TARG_PRPH_RDAT ; 
 int _il_rd (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u32
_il_rd_prph(struct il_priv *il, u32 reg)
{
	_il_wr(il, HBUS_TARG_PRPH_RADDR, reg | (3 << 24));
	return _il_rd(il, HBUS_TARG_PRPH_RDAT);
}