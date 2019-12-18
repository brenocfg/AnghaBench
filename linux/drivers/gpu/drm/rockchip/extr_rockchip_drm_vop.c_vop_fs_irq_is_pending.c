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
 int /*<<< orphan*/  FS_INTR ; 
 int VOP_INTR_GET_TYPE (struct vop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status ; 

__attribute__((used)) static bool vop_fs_irq_is_pending(struct vop *vop)
{
	return VOP_INTR_GET_TYPE(vop, status, FS_INTR);
}