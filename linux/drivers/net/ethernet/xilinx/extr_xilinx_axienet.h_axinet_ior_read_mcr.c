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
typedef  int /*<<< orphan*/  u32 ;
struct axienet_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XAE_MDIO_MCR_OFFSET ; 
 int /*<<< orphan*/  axienet_ior (struct axienet_local*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 axinet_ior_read_mcr(struct axienet_local *lp)
{
	return axienet_ior(lp, XAE_MDIO_MCR_OFFSET);
}