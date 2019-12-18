#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int rth_bkt_sz; int /*<<< orphan*/  rth_algorithm; int /*<<< orphan*/  rth_hash_type_ipv6ex; int /*<<< orphan*/  rth_hash_type_tcpipv6ex; int /*<<< orphan*/  rth_hash_type_ipv6; int /*<<< orphan*/  rth_hash_type_tcpipv6; int /*<<< orphan*/  rth_hash_type_ipv4; int /*<<< orphan*/  rth_hash_type_tcpipv4; } ;
struct vxgedev {int no_of_vpath; TYPE_2__* vpaths; TYPE_1__ config; int /*<<< orphan*/  vp_handles; } ;
struct vxge_hw_rth_hash_types {int /*<<< orphan*/  hash_type_ipv6ex_en; int /*<<< orphan*/  hash_type_tcpipv6ex_en; int /*<<< orphan*/  hash_type_ipv6_en; int /*<<< orphan*/  hash_type_tcpipv6_en; int /*<<< orphan*/  hash_type_ipv4_en; int /*<<< orphan*/  hash_type_tcpipv4_en; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_4__ {int /*<<< orphan*/  device_id; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXGE_ERR ; 
 int VXGE_HW_OK ; 
 int /*<<< orphan*/  vxge_debug_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int vxge_hw_vpath_rts_rth_itable_set (int /*<<< orphan*/ ,int,int*,int*,int) ; 
 int vxge_hw_vpath_rts_rth_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vxge_hw_rth_hash_types*,int) ; 

__attribute__((used)) static enum vxge_hw_status vxge_rth_configure(struct vxgedev *vdev)
{
	enum vxge_hw_status status = VXGE_HW_OK;
	struct vxge_hw_rth_hash_types hash_types;
	u8 itable[256] = {0}; /* indirection table */
	u8 mtable[256] = {0}; /* CPU to vpath mapping  */
	int index;

	/*
	 * Filling
	 * 	- itable with bucket numbers
	 * 	- mtable with bucket-to-vpath mapping
	 */
	for (index = 0; index < (1 << vdev->config.rth_bkt_sz); index++) {
		itable[index] = index;
		mtable[index] = index % vdev->no_of_vpath;
	}

	/* set indirection table, bucket-to-vpath mapping */
	status = vxge_hw_vpath_rts_rth_itable_set(vdev->vp_handles,
						vdev->no_of_vpath,
						mtable, itable,
						vdev->config.rth_bkt_sz);
	if (status != VXGE_HW_OK) {
		vxge_debug_init(VXGE_ERR,
			"RTH indirection table configuration failed "
			"for vpath:%d", vdev->vpaths[0].device_id);
		return status;
	}

	/* Fill RTH hash types */
	hash_types.hash_type_tcpipv4_en   = vdev->config.rth_hash_type_tcpipv4;
	hash_types.hash_type_ipv4_en      = vdev->config.rth_hash_type_ipv4;
	hash_types.hash_type_tcpipv6_en   = vdev->config.rth_hash_type_tcpipv6;
	hash_types.hash_type_ipv6_en      = vdev->config.rth_hash_type_ipv6;
	hash_types.hash_type_tcpipv6ex_en =
					vdev->config.rth_hash_type_tcpipv6ex;
	hash_types.hash_type_ipv6ex_en    = vdev->config.rth_hash_type_ipv6ex;

	/*
	 * Because the itable_set() method uses the active_table field
	 * for the target virtual path the RTH config should be updated
	 * for all VPATHs. The h/w only uses the lowest numbered VPATH
	 * when steering frames.
	 */
	for (index = 0; index < vdev->no_of_vpath; index++) {
		status = vxge_hw_vpath_rts_rth_set(
				vdev->vpaths[index].handle,
				vdev->config.rth_algorithm,
				&hash_types,
				vdev->config.rth_bkt_sz);
		if (status != VXGE_HW_OK) {
			vxge_debug_init(VXGE_ERR,
				"RTH configuration failed for vpath:%d",
				vdev->vpaths[index].device_id);
			return status;
		}
	}

	return status;
}