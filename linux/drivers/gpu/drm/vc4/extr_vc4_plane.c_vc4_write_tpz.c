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
struct vc4_plane_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCALER_TPZ0_IPHASE ; 
 int /*<<< orphan*/  SCALER_TPZ0_SCALE ; 
 int /*<<< orphan*/  SCALER_TPZ1_RECIP ; 
 int VC4_SET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_dlist_write (struct vc4_plane_state*,int) ; 

__attribute__((used)) static void vc4_write_tpz(struct vc4_plane_state *vc4_state, u32 src, u32 dst)
{
	u32 scale, recip;

	scale = (1 << 16) * src / dst;

	/* The specs note that while the reciprocal would be defined
	 * as (1<<32)/scale, ~0 is close enough.
	 */
	recip = ~0 / scale;

	vc4_dlist_write(vc4_state,
			VC4_SET_FIELD(scale, SCALER_TPZ0_SCALE) |
			VC4_SET_FIELD(0, SCALER_TPZ0_IPHASE));
	vc4_dlist_write(vc4_state,
			VC4_SET_FIELD(recip, SCALER_TPZ1_RECIP));
}