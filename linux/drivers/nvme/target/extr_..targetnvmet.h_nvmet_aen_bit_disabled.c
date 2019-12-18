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
struct nvmet_ctrl {int /*<<< orphan*/  aen_masked; int /*<<< orphan*/  aen_enabled; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool nvmet_aen_bit_disabled(struct nvmet_ctrl *ctrl, u32 bn)
{
	if (!(READ_ONCE(ctrl->aen_enabled) & (1 << bn)))
		return true;
	return test_and_set_bit(bn, &ctrl->aen_masked);
}