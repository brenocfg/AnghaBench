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
struct meson_drm {scalar_t__ io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPU_RDARB_MODE_L1C1 ; 
 int /*<<< orphan*/  VPU_RDARB_MODE_L1C2 ; 
 int /*<<< orphan*/  VPU_RDARB_MODE_L2C1 ; 
 int VPU_RDARB_SLAVE_TO_MASTER_PORT (int,int) ; 
 int /*<<< orphan*/  VPU_WRARB_MODE_L2C1 ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void meson_vpu_init(struct meson_drm *priv)
{
	u32 value;

	/*
	 * Slave dc0 and dc5 connected to master port 1.
	 * By default other slaves are connected to master port 0.
	 */
	value = VPU_RDARB_SLAVE_TO_MASTER_PORT(0, 1) |
		VPU_RDARB_SLAVE_TO_MASTER_PORT(5, 1);
	writel_relaxed(value, priv->io_base + _REG(VPU_RDARB_MODE_L1C1));

	/* Slave dc0 connected to master port 1 */
	value = VPU_RDARB_SLAVE_TO_MASTER_PORT(0, 1);
	writel_relaxed(value, priv->io_base + _REG(VPU_RDARB_MODE_L1C2));

	/* Slave dc4 and dc7 connected to master port 1 */
	value = VPU_RDARB_SLAVE_TO_MASTER_PORT(4, 1) |
		VPU_RDARB_SLAVE_TO_MASTER_PORT(7, 1);
	writel_relaxed(value, priv->io_base + _REG(VPU_RDARB_MODE_L2C1));

	/* Slave dc1 connected to master port 1 */
	value = VPU_RDARB_SLAVE_TO_MASTER_PORT(1, 1);
	writel_relaxed(value, priv->io_base + _REG(VPU_WRARB_MODE_L2C1));
}