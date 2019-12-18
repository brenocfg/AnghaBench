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
struct niu {int flags; } ;

/* Variables and functions */
 int NIU_FLAGS_XMAC ; 
 int niu_reset_tx_bmac (struct niu*) ; 
 int niu_reset_tx_xmac (struct niu*) ; 

__attribute__((used)) static int niu_reset_tx_mac(struct niu *np)
{
	if (np->flags & NIU_FLAGS_XMAC)
		return niu_reset_tx_xmac(np);
	else
		return niu_reset_tx_bmac(np);
}