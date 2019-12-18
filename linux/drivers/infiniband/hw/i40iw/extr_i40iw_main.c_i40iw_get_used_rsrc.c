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
struct i40iw_device {int /*<<< orphan*/  max_mr; int /*<<< orphan*/  allocated_mrs; void* used_mrs; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  allocated_cqs; void* used_cqs; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  allocated_qps; void* used_qps; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  allocated_pds; void* used_pds; } ;

/* Variables and functions */
 void* find_next_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40iw_get_used_rsrc(struct i40iw_device *iwdev)
{
	iwdev->used_pds = find_next_zero_bit(iwdev->allocated_pds, iwdev->max_pd, 0);
	iwdev->used_qps = find_next_zero_bit(iwdev->allocated_qps, iwdev->max_qp, 0);
	iwdev->used_cqs = find_next_zero_bit(iwdev->allocated_cqs, iwdev->max_cq, 0);
	iwdev->used_mrs = find_next_zero_bit(iwdev->allocated_mrs, iwdev->max_mr, 0);
}