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
struct mvneta_bm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_BM_INTR_CAUSE_REG ; 
 int /*<<< orphan*/  MVNETA_BM_POOL_BASE_REG (int) ; 
 int /*<<< orphan*/  MVNETA_BM_POOL_ENABLE_MASK ; 
 int /*<<< orphan*/  mvneta_bm_read (struct mvneta_bm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_bm_write (struct mvneta_bm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_bm_pool_enable(struct mvneta_bm *priv, int pool_id)
{
	u32 val;

	val = mvneta_bm_read(priv, MVNETA_BM_POOL_BASE_REG(pool_id));
	val |= MVNETA_BM_POOL_ENABLE_MASK;
	mvneta_bm_write(priv, MVNETA_BM_POOL_BASE_REG(pool_id), val);

	/* Clear BM cause register */
	mvneta_bm_write(priv, MVNETA_BM_INTR_CAUSE_REG, 0);
}