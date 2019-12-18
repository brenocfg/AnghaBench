#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  gl_adapt_enable; } ;
struct TYPE_8__ {TYPE_3__ coal; } ;
struct TYPE_5__ {int /*<<< orphan*/  gl_adapt_enable; } ;
struct TYPE_6__ {TYPE_1__ coal; } ;
struct hns3_enet_tqp_vector {scalar_t__ mask_addr; TYPE_4__ rx_group; TYPE_2__ tx_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_INT_RL_ENABLE_MASK ; 
 scalar_t__ HNS3_VECTOR_RL_OFFSET ; 
 int /*<<< orphan*/  hns3_rl_usec_to_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void hns3_set_vector_coalesce_rl(struct hns3_enet_tqp_vector *tqp_vector,
				 u32 rl_value)
{
	u32 rl_reg = hns3_rl_usec_to_reg(rl_value);

	/* this defines the configuration for RL (Interrupt Rate Limiter).
	 * Rl defines rate of interrupts i.e. number of interrupts-per-second
	 * GL and RL(Rate Limiter) are 2 ways to acheive interrupt coalescing
	 */

	if (rl_reg > 0 && !tqp_vector->tx_group.coal.gl_adapt_enable &&
	    !tqp_vector->rx_group.coal.gl_adapt_enable)
		/* According to the hardware, the range of rl_reg is
		 * 0-59 and the unit is 4.
		 */
		rl_reg |=  HNS3_INT_RL_ENABLE_MASK;

	writel(rl_reg, tqp_vector->mask_addr + HNS3_VECTOR_RL_OFFSET);
}