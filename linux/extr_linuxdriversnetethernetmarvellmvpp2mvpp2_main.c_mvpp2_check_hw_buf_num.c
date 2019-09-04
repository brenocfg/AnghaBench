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
struct mvpp2_bm_pool {int /*<<< orphan*/  id; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int MVPP22_BM_POOL_PTRS_NUM_MASK ; 
 int /*<<< orphan*/  MVPP2_BM_BPPI_PTRS_NUM_REG (int /*<<< orphan*/ ) ; 
 int MVPP2_BM_BPPI_PTR_NUM_MASK ; 
 int /*<<< orphan*/  MVPP2_BM_POOL_PTRS_NUM_REG (int /*<<< orphan*/ ) ; 
 int mvpp2_read (struct mvpp2*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvpp2_check_hw_buf_num(struct mvpp2 *priv, struct mvpp2_bm_pool *bm_pool)
{
	int buf_num = 0;

	buf_num += mvpp2_read(priv, MVPP2_BM_POOL_PTRS_NUM_REG(bm_pool->id)) &
				    MVPP22_BM_POOL_PTRS_NUM_MASK;
	buf_num += mvpp2_read(priv, MVPP2_BM_BPPI_PTRS_NUM_REG(bm_pool->id)) &
				    MVPP2_BM_BPPI_PTR_NUM_MASK;

	/* HW has one buffer ready which is not reflected in the counters */
	if (buf_num)
		buf_num += 1;

	return buf_num;
}