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
struct mvpp2_bm_pool {int buf_size; int /*<<< orphan*/  id; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int MVPP2_POOL_BUF_SIZE_OFFSET ; 
 int /*<<< orphan*/  MVPP2_POOL_BUF_SIZE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_bm_pool_bufsize_set(struct mvpp2 *priv,
				      struct mvpp2_bm_pool *bm_pool,
				      int buf_size)
{
	u32 val;

	bm_pool->buf_size = buf_size;

	val = ALIGN(buf_size, 1 << MVPP2_POOL_BUF_SIZE_OFFSET);
	mvpp2_write(priv, MVPP2_POOL_BUF_SIZE_REG(bm_pool->id), val);
}