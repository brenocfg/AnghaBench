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
struct mlxsw_sp_fid_family {int /*<<< orphan*/  fids_bitmap; scalar_t__ start_index; TYPE_1__* ops; } ;
struct mlxsw_sp_fid {int ref_count; scalar_t__ fid_index; struct mlxsw_sp_fid_family* fid_family; int /*<<< orphan*/  list; scalar_t__ rif; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* deconfigure ) (struct mlxsw_sp_fid*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_fid*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 void mlxsw_sp_rif_destroy (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_fid*) ; 

void mlxsw_sp_fid_put(struct mlxsw_sp_fid *fid)
{
	struct mlxsw_sp_fid_family *fid_family = fid->fid_family;

	if (--fid->ref_count == 1 && fid->rif) {
		/* Destroy the associated RIF and let it drop the last
		 * reference on the FID.
		 */
		return mlxsw_sp_rif_destroy(fid->rif);
	} else if (fid->ref_count == 0) {
		list_del(&fid->list);
		fid->fid_family->ops->deconfigure(fid);
		__clear_bit(fid->fid_index - fid_family->start_index,
			    fid_family->fids_bitmap);
		kfree(fid);
	}
}