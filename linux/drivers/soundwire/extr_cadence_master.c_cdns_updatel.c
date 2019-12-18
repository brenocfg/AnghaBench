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
struct sdw_cdns {int dummy; } ;

/* Variables and functions */
 int cdns_readl (struct sdw_cdns*,int) ; 
 int /*<<< orphan*/  cdns_writel (struct sdw_cdns*,int,int) ; 

__attribute__((used)) static inline void cdns_updatel(struct sdw_cdns *cdns,
				int offset, u32 mask, u32 val)
{
	u32 tmp;

	tmp = cdns_readl(cdns, offset);
	tmp = (tmp & ~mask) | val;
	cdns_writel(cdns, offset, tmp);
}