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
typedef  scalar_t__ u32 ;
struct bcm_sysport_priv {scalar_t__ base; scalar_t__ is_lite; } ;

/* Variables and functions */
 scalar_t__ RDMA_STATUS ; 
 scalar_t__ SYS_PORT_RDMA_OFFSET ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void rdma_writel(struct bcm_sysport_priv *priv, u32 val, u32 off)
{
	if (priv->is_lite && off >= RDMA_STATUS)
		off += 4;
	writel_relaxed(val, priv->base + SYS_PORT_RDMA_OFFSET + off);
}