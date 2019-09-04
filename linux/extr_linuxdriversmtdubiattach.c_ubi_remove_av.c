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
struct ubi_attach_info {int vols_found; int /*<<< orphan*/  erase; int /*<<< orphan*/  volumes; } ;
struct ubi_ainf_volume {int /*<<< orphan*/  rb; int /*<<< orphan*/  vol_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_bld (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_av (struct ubi_attach_info*,struct ubi_ainf_volume*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ubi_remove_av(struct ubi_attach_info *ai, struct ubi_ainf_volume *av)
{
	dbg_bld("remove attaching information about volume %d", av->vol_id);

	rb_erase(&av->rb, &ai->volumes);
	destroy_av(ai, av, &ai->erase);
	ai->vols_found -= 1;
}