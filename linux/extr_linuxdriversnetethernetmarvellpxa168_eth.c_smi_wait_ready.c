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
struct pxa168_eth_private {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int PHY_WAIT_ITERATIONS ; 
 int /*<<< orphan*/  SMI ; 
 int SMI_BUSY ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rdl (struct pxa168_eth_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smi_wait_ready(struct pxa168_eth_private *pep)
{
	int i = 0;

	/* wait for the SMI register to become available */
	for (i = 0; rdl(pep, SMI) & SMI_BUSY; i++) {
		if (i == PHY_WAIT_ITERATIONS)
			return -ETIMEDOUT;
		msleep(10);
	}

	return 0;
}