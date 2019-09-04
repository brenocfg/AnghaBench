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
typedef  int /*<<< orphan*/  u64 ;
struct sec_queue {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ SEC_Q_BASE_HADDR_REG ; 
 scalar_t__ SEC_Q_BASE_LADDR_REG ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sec_queue_cmdbase_addr(struct sec_queue *queue, u64 addr)
{
	writel_relaxed(upper_32_bits(addr), queue->regs + SEC_Q_BASE_HADDR_REG);
	writel_relaxed(lower_32_bits(addr), queue->regs + SEC_Q_BASE_LADDR_REG);
}