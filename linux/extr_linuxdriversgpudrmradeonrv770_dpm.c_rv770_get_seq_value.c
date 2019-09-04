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
typedef  int /*<<< orphan*/  u8 ;
struct rv7xx_pl {int flags; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int ATOM_PPLIB_R600_FLAGS_LOWPOWER ; 
 int /*<<< orphan*/  MC_CG_SEQ_DRAMCONF_S0 ; 
 int /*<<< orphan*/  MC_CG_SEQ_DRAMCONF_S1 ; 

u8 rv770_get_seq_value(struct radeon_device *rdev,
		       struct rv7xx_pl *pl)
{
	return (pl->flags & ATOM_PPLIB_R600_FLAGS_LOWPOWER) ?
		MC_CG_SEQ_DRAMCONF_S0 : MC_CG_SEQ_DRAMCONF_S1;
}