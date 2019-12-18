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
struct mesh_state {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAC_FTR_MESH_ENABLE ; 
 int /*<<< orphan*/  machine_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macio_get_of_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  powermac ; 

__attribute__((used)) static void set_mesh_power(struct mesh_state *ms, int state)
{
	if (!machine_is(powermac))
		return;
	if (state) {
		pmac_call_feature(PMAC_FTR_MESH_ENABLE, macio_get_of_node(ms->mdev), 0, 1);
		msleep(200);
	} else {
		pmac_call_feature(PMAC_FTR_MESH_ENABLE, macio_get_of_node(ms->mdev), 0, 0);
		msleep(10);
	}
}