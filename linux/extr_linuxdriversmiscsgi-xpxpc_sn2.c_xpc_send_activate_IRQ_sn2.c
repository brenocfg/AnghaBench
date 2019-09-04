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
struct amo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MASK (int) ; 
 size_t BIT_WORD (int) ; 
 int /*<<< orphan*/  SGI_XPC_ACTIVATE ; 
 int XPC_ACTIVATE_IRQ_AMOS_SN2 ; 
 scalar_t__ __va (unsigned long) ; 
 int /*<<< orphan*/  xpc_send_IRQ_sn2 (struct amo*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_send_activate_IRQ_sn2(unsigned long amos_page_pa, int from_nasid,
			  int to_nasid, int to_phys_cpuid)
{
	struct amo *amos = (struct amo *)__va(amos_page_pa +
					      (XPC_ACTIVATE_IRQ_AMOS_SN2 *
					      sizeof(struct amo)));

	(void)xpc_send_IRQ_sn2(&amos[BIT_WORD(from_nasid / 2)],
			       BIT_MASK(from_nasid / 2), to_nasid,
			       to_phys_cpuid, SGI_XPC_ACTIVATE);
}