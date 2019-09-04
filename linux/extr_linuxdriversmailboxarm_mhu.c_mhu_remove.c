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
struct arm_mhu {int /*<<< orphan*/  mbox; } ;
struct amba_device {int dummy; } ;

/* Variables and functions */
 struct arm_mhu* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  mbox_controller_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mhu_remove(struct amba_device *adev)
{
	struct arm_mhu *mhu = amba_get_drvdata(adev);

	mbox_controller_unregister(&mhu->mbox);

	return 0;
}