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
struct tg3 {int /*<<< orphan*/ * rss_ind_tbl; } ;

/* Variables and functions */
 int TG3_RSS_INDIR_TBL_SIZE ; 
 int /*<<< orphan*/  ethtool_rxfh_indir_default (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_rss_init_dflt_indir_tbl(struct tg3 *tp, u32 qcnt)
{
	int i;

	for (i = 0; i < TG3_RSS_INDIR_TBL_SIZE; i++)
		tp->rss_ind_tbl[i] = ethtool_rxfh_indir_default(i, qcnt);
}