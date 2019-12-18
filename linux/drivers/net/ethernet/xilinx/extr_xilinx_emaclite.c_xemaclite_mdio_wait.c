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
struct net_local {scalar_t__ base_addr; } ;

/* Variables and functions */
 int XEL_MDIOCTRL_MDIOSTS_MASK ; 
 scalar_t__ XEL_MDIOCTRL_OFFSET ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  xemaclite_readl ; 

__attribute__((used)) static int xemaclite_mdio_wait(struct net_local *lp)
{
	u32 val;

	/* wait for the MDIO interface to not be busy or timeout
	 * after some time.
	 */
	return readx_poll_timeout(xemaclite_readl,
				  lp->base_addr + XEL_MDIOCTRL_OFFSET,
				  val, !(val & XEL_MDIOCTRL_MDIOSTS_MASK),
				  1000, 20000);
}