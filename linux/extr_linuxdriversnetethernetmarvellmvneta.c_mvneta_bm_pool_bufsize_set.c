#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mvneta_port {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 
 int MVNETA_PORT_POOL_BUFFER_SZ_MASK ; 
 int /*<<< orphan*/  MVNETA_PORT_POOL_BUFFER_SZ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void mvneta_bm_pool_bufsize_set(struct mvneta_port *pp,
					      int buf_size,
					      u8 pool_id)
{
	u32 val;

	if (!IS_ALIGNED(buf_size, 8)) {
		dev_warn(pp->dev->dev.parent,
			 "illegal buf_size value %d, round to %d\n",
			 buf_size, ALIGN(buf_size, 8));
		buf_size = ALIGN(buf_size, 8);
	}

	val = mvreg_read(pp, MVNETA_PORT_POOL_BUFFER_SZ_REG(pool_id));
	val |= buf_size & MVNETA_PORT_POOL_BUFFER_SZ_MASK;
	mvreg_write(pp, MVNETA_PORT_POOL_BUFFER_SZ_REG(pool_id), val);
}