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
struct mic_device {int family; int /*<<< orphan*/ * smpt_ops; int /*<<< orphan*/ * intr_ops; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
#define  MIC_FAMILY_X100 128 
 int /*<<< orphan*/  mic_x100_intr_ops ; 
 int /*<<< orphan*/  mic_x100_ops ; 
 int /*<<< orphan*/  mic_x100_smpt_ops ; 

__attribute__((used)) static void mic_ops_init(struct mic_device *mdev)
{
	switch (mdev->family) {
	case MIC_FAMILY_X100:
		mdev->ops = &mic_x100_ops;
		mdev->intr_ops = &mic_x100_intr_ops;
		mdev->smpt_ops = &mic_x100_smpt_ops;
		break;
	default:
		break;
	}
}