#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mic_thread_lock; int /*<<< orphan*/  mic_intr_lock; int /*<<< orphan*/  cb_ida; int /*<<< orphan*/ * cb_list; } ;
struct mic_device {TYPE_1__ irq_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MIC_NUM_OFFSETS ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mic_setup_callbacks(struct mic_device *mdev)
{
	int i;

	mdev->irq_info.cb_list = kmalloc_array(MIC_NUM_OFFSETS,
					       sizeof(*mdev->irq_info.cb_list),
					       GFP_KERNEL);
	if (!mdev->irq_info.cb_list)
		return -ENOMEM;

	for (i = 0; i < MIC_NUM_OFFSETS; i++)
		INIT_LIST_HEAD(&mdev->irq_info.cb_list[i]);
	ida_init(&mdev->irq_info.cb_ida);
	spin_lock_init(&mdev->irq_info.mic_intr_lock);
	spin_lock_init(&mdev->irq_info.mic_thread_lock);
	return 0;
}