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
struct fwtty_peer {int generation; int /*<<< orphan*/  node_id; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;
struct fw_device {int generation; int /*<<< orphan*/  node_id; } ;

/* Variables and functions */
 struct fwtty_peer* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct fw_device* fw_parent_device (struct fw_unit*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void fwserial_update(struct fw_unit *unit)
{
	struct fw_device *parent = fw_parent_device(unit);
	struct fwtty_peer *peer = dev_get_drvdata(&unit->device);
	int generation;

	generation = parent->generation;
	smp_rmb();
	peer->node_id = parent->node_id;
	smp_wmb();
	peer->generation = generation;
}