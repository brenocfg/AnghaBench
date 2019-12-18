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
struct mtk_vpu {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VPU_RESET ; 
 int vpu_cfg_readl (struct mtk_vpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool vpu_running(struct mtk_vpu *vpu)
{
	return vpu_cfg_readl(vpu, VPU_RESET) & BIT(0);
}