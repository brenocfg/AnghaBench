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
struct tg3 {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPU_MODE ; 
 int /*<<< orphan*/  CPU_MODE_HALT ; 
 scalar_t__ CPU_STATE ; 
 scalar_t__ RX_CPU_BASE ; 
 int tg3_pause_cpu (struct tg3*,scalar_t__) ; 
 int /*<<< orphan*/  tw32 (scalar_t__,int) ; 
 int /*<<< orphan*/  tw32_f (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tg3_rxcpu_pause(struct tg3 *tp)
{
	int rc = tg3_pause_cpu(tp, RX_CPU_BASE);

	tw32(RX_CPU_BASE + CPU_STATE, 0xffffffff);
	tw32_f(RX_CPU_BASE + CPU_MODE,  CPU_MODE_HALT);
	udelay(10);

	return rc;
}