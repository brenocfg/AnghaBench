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
struct tg3 {int* rss_ind_tbl; } ;

/* Variables and functions */
 int MAC_RSS_INDIR_TBL_0 ; 
 int TG3_RSS_INDIR_TBL_SIZE ; 
 int /*<<< orphan*/  tw32 (int,int) ; 

__attribute__((used)) static void tg3_rss_write_indir_tbl(struct tg3 *tp)
{
	int i = 0;
	u32 reg = MAC_RSS_INDIR_TBL_0;

	while (i < TG3_RSS_INDIR_TBL_SIZE) {
		u32 val = tp->rss_ind_tbl[i];
		i++;
		for (; i % 8; i++) {
			val <<= 4;
			val |= tp->rss_ind_tbl[i];
		}
		tw32(reg, val);
		reg += 4;
	}
}