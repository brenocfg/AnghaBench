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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MDP5_IRQ_INTF0_UNDER_RUN ; 
 int /*<<< orphan*/  MDP5_IRQ_INTF1_UNDER_RUN ; 
 int /*<<< orphan*/  MDP5_IRQ_INTF2_UNDER_RUN ; 
 int /*<<< orphan*/  MDP5_IRQ_INTF3_UNDER_RUN ; 

__attribute__((used)) static inline uint32_t intf2err(int intf_num)
{
	switch (intf_num) {
	case 0:  return MDP5_IRQ_INTF0_UNDER_RUN;
	case 1:  return MDP5_IRQ_INTF1_UNDER_RUN;
	case 2:  return MDP5_IRQ_INTF2_UNDER_RUN;
	case 3:  return MDP5_IRQ_INTF3_UNDER_RUN;
	default: return 0;
	}
}