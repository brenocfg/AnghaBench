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
struct meson_drm {scalar_t__ io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPU_RDARB_MODE_L1C1 ; 
 int /*<<< orphan*/  VPU_RDARB_MODE_L1C2 ; 
 int /*<<< orphan*/  VPU_RDARB_MODE_L2C1 ; 
 int /*<<< orphan*/  VPU_WRARB_MODE_L2C1 ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void meson_vpu_init(struct meson_drm *priv)
{
	writel_relaxed(0x210000, priv->io_base + _REG(VPU_RDARB_MODE_L1C1));
	writel_relaxed(0x10000, priv->io_base + _REG(VPU_RDARB_MODE_L1C2));
	writel_relaxed(0x900000, priv->io_base + _REG(VPU_RDARB_MODE_L2C1));
	writel_relaxed(0x20000, priv->io_base + _REG(VPU_WRARB_MODE_L2C1));
}