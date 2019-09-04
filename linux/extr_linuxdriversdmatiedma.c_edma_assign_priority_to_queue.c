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
struct edma_cc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDMA_QUEPRI ; 
 int /*<<< orphan*/  edma_modify (struct edma_cc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void edma_assign_priority_to_queue(struct edma_cc *ecc, int queue_no,
					  int priority)
{
	int bit = queue_no * 4;

	edma_modify(ecc, EDMA_QUEPRI, ~(0x7 << bit), ((priority & 0x7) << bit));
}