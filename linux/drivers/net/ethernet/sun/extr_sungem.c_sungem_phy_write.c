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
typedef  int /*<<< orphan*/  u16 ;
struct gem {int /*<<< orphan*/  mii_phy_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sungem_phy_write (struct gem*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sungem_phy_write(struct gem *gp, int reg, u16 val)
{
	__sungem_phy_write(gp, gp->mii_phy_addr, reg, val);
}