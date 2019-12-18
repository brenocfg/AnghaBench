#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pqi_ctrl_info {TYPE_1__* registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  sis_host_to_ctrl_doorbell; } ;

/* Variables and functions */
 int sis_wait_for_doorbell_bit_to_clear (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int sis_set_doorbell_bit(struct pqi_ctrl_info *ctrl_info, u32 bit)
{
	writel(bit, &ctrl_info->registers->sis_host_to_ctrl_doorbell);

	return sis_wait_for_doorbell_bit_to_clear(ctrl_info, bit);
}