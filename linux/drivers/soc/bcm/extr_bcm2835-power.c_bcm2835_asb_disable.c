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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct bcm2835_power {int dummy; } ;

/* Variables and functions */
 int ASB_ACK ; 
 int ASB_READ (int /*<<< orphan*/ ) ; 
 int ASB_REQ_STOP ; 
 int /*<<< orphan*/  ASB_WRITE (int /*<<< orphan*/ ,int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int ktime_get_ns () ; 

__attribute__((used)) static int bcm2835_asb_disable(struct bcm2835_power *power, u32 reg)
{
	u64 start;

	if (!reg)
		return 0;

	start = ktime_get_ns();

	/* Enable the module's async AXI bridges. */
	ASB_WRITE(reg, ASB_READ(reg) | ASB_REQ_STOP);
	while (!(ASB_READ(reg) & ASB_ACK)) {
		cpu_relax();
		if (ktime_get_ns() - start >= 1000)
			return -ETIMEDOUT;
	}

	return 0;
}