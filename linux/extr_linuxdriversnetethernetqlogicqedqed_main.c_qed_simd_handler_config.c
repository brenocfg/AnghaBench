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
struct qed_hwfn {TYPE_1__* simd_proto_handler; } ;
struct qed_dev {int num_hwfns; struct qed_hwfn* hwfns; } ;
struct TYPE_2__ {void (* func ) (void*) ;void* token; } ;

/* Variables and functions */

__attribute__((used)) static void qed_simd_handler_config(struct qed_dev *cdev, void *token,
				    int index, void(*handler)(void *))
{
	struct qed_hwfn *hwfn = &cdev->hwfns[index % cdev->num_hwfns];
	int relative_idx = index / cdev->num_hwfns;

	hwfn->simd_proto_handler[relative_idx].func = handler;
	hwfn->simd_proto_handler[relative_idx].token = token;
}