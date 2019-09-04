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
struct TYPE_2__ {int /*<<< orphan*/  pkt_size; int /*<<< orphan*/  buf_num; } ;

/* Variables and functions */
 size_t MVPP2_BM_JUMBO ; 
 int /*<<< orphan*/  MVPP2_BM_JUMBO_BUF_NUM ; 
 int /*<<< orphan*/  MVPP2_BM_JUMBO_PKT_SIZE ; 
 size_t MVPP2_BM_LONG ; 
 int /*<<< orphan*/  MVPP2_BM_LONG_BUF_NUM ; 
 int /*<<< orphan*/  MVPP2_BM_LONG_PKT_SIZE ; 
 size_t MVPP2_BM_SHORT ; 
 int /*<<< orphan*/  MVPP2_BM_SHORT_BUF_NUM ; 
 int /*<<< orphan*/  MVPP2_BM_SHORT_PKT_SIZE ; 
 TYPE_1__* mvpp2_pools ; 

__attribute__((used)) static void mvpp2_setup_bm_pool(void)
{
	/* Short pool */
	mvpp2_pools[MVPP2_BM_SHORT].buf_num  = MVPP2_BM_SHORT_BUF_NUM;
	mvpp2_pools[MVPP2_BM_SHORT].pkt_size = MVPP2_BM_SHORT_PKT_SIZE;

	/* Long pool */
	mvpp2_pools[MVPP2_BM_LONG].buf_num  = MVPP2_BM_LONG_BUF_NUM;
	mvpp2_pools[MVPP2_BM_LONG].pkt_size = MVPP2_BM_LONG_PKT_SIZE;

	/* Jumbo pool */
	mvpp2_pools[MVPP2_BM_JUMBO].buf_num  = MVPP2_BM_JUMBO_BUF_NUM;
	mvpp2_pools[MVPP2_BM_JUMBO].pkt_size = MVPP2_BM_JUMBO_PKT_SIZE;
}