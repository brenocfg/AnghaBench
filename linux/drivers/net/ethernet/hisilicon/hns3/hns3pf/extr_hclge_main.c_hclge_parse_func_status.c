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
struct hclge_func_status_cmd {int pf_state; } ;
struct hclge_dev {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCLGE_FLAG_MAIN ; 
 int HCLGE_PF_STATE_DONE ; 
 int HCLGE_PF_STATE_MAIN ; 

__attribute__((used)) static int hclge_parse_func_status(struct hclge_dev *hdev,
				   struct hclge_func_status_cmd *status)
{
	if (!(status->pf_state & HCLGE_PF_STATE_DONE))
		return -EINVAL;

	/* Set the pf to main pf */
	if (status->pf_state & HCLGE_PF_STATE_MAIN)
		hdev->flag |= HCLGE_FLAG_MAIN;
	else
		hdev->flag &= ~HCLGE_FLAG_MAIN;

	return 0;
}