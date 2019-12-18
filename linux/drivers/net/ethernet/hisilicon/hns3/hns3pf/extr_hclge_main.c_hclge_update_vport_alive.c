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
struct hclge_vport {int /*<<< orphan*/  mps; int /*<<< orphan*/  state; scalar_t__ last_active_jiffies; } ;
struct hclge_dev {int num_alloc_vport; struct hclge_vport* vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MAC_DEFAULT_FRAME ; 
 int /*<<< orphan*/  HCLGE_VPORT_STATE_ALIVE ; 
 int HZ ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hclge_update_vport_alive(struct hclge_dev *hdev)
{
	int i;

	/* start from vport 1 for PF is always alive */
	for (i = 1; i < hdev->num_alloc_vport; i++) {
		struct hclge_vport *vport = &hdev->vport[i];

		if (time_after(jiffies, vport->last_active_jiffies + 8 * HZ))
			clear_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state);

		/* If vf is not alive, set to default value */
		if (!test_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state))
			vport->mps = HCLGE_MAC_DEFAULT_FRAME;
	}
}