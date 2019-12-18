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
typedef  int /*<<< orphan*/  u8 ;
struct ath10k {int /*<<< orphan*/ * mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_VDEV_SUBTYPE_NONE ; 
 int WMI_VDEV_TYPE_STA ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int ath10k_wmi_barrier (struct ath10k*) ; 
 int ath10k_wmi_get_vdev_subtype (struct ath10k*,int /*<<< orphan*/ ) ; 
 int ath10k_wmi_vdev_create (struct ath10k*,int,int,int,int /*<<< orphan*/  const*) ; 
 int ath10k_wmi_vdev_delete (struct ath10k*,int) ; 

__attribute__((used)) static int ath10k_core_reset_rx_filter(struct ath10k *ar)
{
	int ret;
	int vdev_id;
	int vdev_type;
	int vdev_subtype;
	const u8 *vdev_addr;

	vdev_id = 0;
	vdev_type = WMI_VDEV_TYPE_STA;
	vdev_subtype = ath10k_wmi_get_vdev_subtype(ar, WMI_VDEV_SUBTYPE_NONE);
	vdev_addr = ar->mac_addr;

	ret = ath10k_wmi_vdev_create(ar, vdev_id, vdev_type, vdev_subtype,
				     vdev_addr);
	if (ret) {
		ath10k_err(ar, "failed to create dummy vdev: %d\n", ret);
		return ret;
	}

	ret = ath10k_wmi_vdev_delete(ar, vdev_id);
	if (ret) {
		ath10k_err(ar, "failed to delete dummy vdev: %d\n", ret);
		return ret;
	}

	/* WMI and HTT may use separate HIF pipes and are not guaranteed to be
	 * serialized properly implicitly.
	 *
	 * Moreover (most) WMI commands have no explicit acknowledges. It is
	 * possible to infer it implicitly by poking firmware with echo
	 * command - getting a reply means all preceding comments have been
	 * (mostly) processed.
	 *
	 * In case of vdev create/delete this is sufficient.
	 *
	 * Without this it's possible to end up with a race when HTT Rx ring is
	 * started before vdev create/delete hack is complete allowing a short
	 * window of opportunity to receive (and Tx ACK) a bunch of frames.
	 */
	ret = ath10k_wmi_barrier(ar);
	if (ret) {
		ath10k_err(ar, "failed to ping firmware: %d\n", ret);
		return ret;
	}

	return 0;
}