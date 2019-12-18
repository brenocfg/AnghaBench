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
struct drm_dp_aux_msg {int /*<<< orphan*/  request; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP0_AUXCFG0_ADDR_ONLY ; 
 int /*<<< orphan*/  DP0_AUXCFG0_BSIZE ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static u32 tc_auxcfg0(struct drm_dp_aux_msg *msg, size_t size)
{
	u32 auxcfg0 = msg->request;

	if (size)
		auxcfg0 |= FIELD_PREP(DP0_AUXCFG0_BSIZE, size - 1);
	else
		auxcfg0 |= DP0_AUXCFG0_ADDR_ONLY;

	return auxcfg0;
}