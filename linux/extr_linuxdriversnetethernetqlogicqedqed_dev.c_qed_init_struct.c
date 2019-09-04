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
typedef  size_t u8 ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct qed_hwfn {size_t my_id; int b_active; TYPE_1__ dmae_info; struct qed_dev* cdev; } ;
struct qed_dev {int cache_shift; struct qed_hwfn* hwfns; } ;

/* Variables and functions */
 size_t MAX_HWFNS_PER_DEVICE ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void qed_init_struct(struct qed_dev *cdev)
{
	u8 i;

	for (i = 0; i < MAX_HWFNS_PER_DEVICE; i++) {
		struct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		p_hwfn->cdev = cdev;
		p_hwfn->my_id = i;
		p_hwfn->b_active = false;

		mutex_init(&p_hwfn->dmae_info.mutex);
	}

	/* hwfn 0 is always active */
	cdev->hwfns[0].b_active = true;

	/* set the default cache alignment to 128 */
	cdev->cache_shift = 7;
}