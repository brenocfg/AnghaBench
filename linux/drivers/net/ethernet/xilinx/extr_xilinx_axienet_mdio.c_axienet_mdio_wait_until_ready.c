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
struct axienet_local {int dummy; } ;

/* Variables and functions */
 int XAE_MDIO_MCR_READY_MASK ; 
 int /*<<< orphan*/  axinet_ior_read_mcr ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,struct axienet_local*,int,int,int,int) ; 

__attribute__((used)) static int axienet_mdio_wait_until_ready(struct axienet_local *lp)
{
	u32 val;

	return readx_poll_timeout(axinet_ior_read_mcr, lp,
				  val, val & XAE_MDIO_MCR_READY_MASK,
				  1, 20000);
}