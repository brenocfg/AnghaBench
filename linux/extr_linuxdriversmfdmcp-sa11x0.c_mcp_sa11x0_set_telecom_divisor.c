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
struct mcp_sa11x0 {int mccr0; } ;
struct mcp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCCR0 (struct mcp_sa11x0*) ; 
 struct mcp_sa11x0* priv (struct mcp*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mcp_sa11x0_set_telecom_divisor(struct mcp *mcp, unsigned int divisor)
{
	struct mcp_sa11x0 *m = priv(mcp);

	divisor /= 32;

	m->mccr0 &= ~0x00007f00;
	m->mccr0 |= divisor << 8;
	writel_relaxed(m->mccr0, MCCR0(m));
}