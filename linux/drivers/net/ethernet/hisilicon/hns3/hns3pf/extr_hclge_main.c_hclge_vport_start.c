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
struct hclge_vport {int /*<<< orphan*/  last_active_jiffies; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_VPORT_STATE_ALIVE ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hclge_vport_start(struct hclge_vport *vport)
{
	set_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state);
	vport->last_active_jiffies = jiffies;
	return 0;
}