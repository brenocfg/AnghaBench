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
struct vop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOP_REG_SET (struct vop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfg_done ; 
 int /*<<< orphan*/  common ; 

__attribute__((used)) static inline void vop_cfg_done(struct vop *vop)
{
	VOP_REG_SET(vop, common, cfg_done, 1);
}