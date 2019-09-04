#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct xge_pdata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int XGE_EXTD_STATS_LEN ; 
 TYPE_1__* gstrings_extd_stats ; 
 scalar_t__ xge_rd_csr (struct xge_pdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xge_mac_get_extd_stats(struct xge_pdata *pdata)
{
	u32 data;
	int i;

	for (i = 0; i < XGE_EXTD_STATS_LEN; i++) {
		data = xge_rd_csr(pdata, gstrings_extd_stats[i].addr);
		gstrings_extd_stats[i].value += data;
	}
}