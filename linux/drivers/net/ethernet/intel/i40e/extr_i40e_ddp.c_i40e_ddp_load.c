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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_profile_segment {int /*<<< orphan*/  name; int /*<<< orphan*/  version; } ;
struct i40e_profile_section_header {int dummy; } ;
struct i40e_profile_info {int /*<<< orphan*/  name; int /*<<< orphan*/  op; int /*<<< orphan*/  version; int /*<<< orphan*/  track_id; } ;
struct i40e_pf {int /*<<< orphan*/  hw; } ;
struct i40e_package_header {int dummy; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
struct i40e_metadata_segment {int /*<<< orphan*/  track_id; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EPERM ; 
 int /*<<< orphan*/  I40E_DDP_ADD_TRACKID ; 
 int /*<<< orphan*/  I40E_DDP_NAME_SIZE ; 
 int /*<<< orphan*/  I40E_DDP_REMOVE_TRACKID ; 
 scalar_t__ I40E_ERR_DEVICE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  SEGMENT_TYPE_I40E ; 
 int /*<<< orphan*/  SEGMENT_TYPE_METADATA ; 
 scalar_t__ i40e_add_pinfo (int /*<<< orphan*/ *,struct i40e_profile_segment*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int i40e_ddp_does_profile_exist (int /*<<< orphan*/ *,struct i40e_profile_info*) ; 
 int i40e_ddp_does_profile_overlap (int /*<<< orphan*/ *,struct i40e_profile_info*) ; 
 int /*<<< orphan*/  i40e_ddp_is_pkg_hdr_valid (struct net_device*,struct i40e_package_header*,size_t) ; 
 scalar_t__ i40e_del_pinfo (int /*<<< orphan*/ *,struct i40e_profile_segment*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_find_segment_in_package (int /*<<< orphan*/ ,struct i40e_package_header*) ; 
 scalar_t__ i40e_rollback_profile (int /*<<< orphan*/ *,struct i40e_profile_segment*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_write_profile (int /*<<< orphan*/ *,struct i40e_profile_segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

int i40e_ddp_load(struct net_device *netdev, const u8 *data, size_t size,
		  bool is_add)
{
	u8 profile_info_sec[sizeof(struct i40e_profile_section_header) +
			    sizeof(struct i40e_profile_info)];
	struct i40e_metadata_segment *metadata_hdr;
	struct i40e_profile_segment *profile_hdr;
	struct i40e_profile_info pinfo;
	struct i40e_package_header *pkg_hdr;
	i40e_status status;
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	u32 track_id;
	int istatus;

	pkg_hdr = (struct i40e_package_header *)data;
	if (!i40e_ddp_is_pkg_hdr_valid(netdev, pkg_hdr, size))
		return -EINVAL;

	if (size < (sizeof(struct i40e_package_header) +
		    sizeof(struct i40e_metadata_segment) + sizeof(u32) * 2)) {
		netdev_err(netdev, "Invalid DDP recipe size.");
		return -EINVAL;
	}

	/* Find beginning of segment data in buffer */
	metadata_hdr = (struct i40e_metadata_segment *)
		i40e_find_segment_in_package(SEGMENT_TYPE_METADATA, pkg_hdr);
	if (!metadata_hdr) {
		netdev_err(netdev, "Failed to find metadata segment in DDP recipe.");
		return -EINVAL;
	}

	track_id = metadata_hdr->track_id;
	profile_hdr = (struct i40e_profile_segment *)
		i40e_find_segment_in_package(SEGMENT_TYPE_I40E, pkg_hdr);
	if (!profile_hdr) {
		netdev_err(netdev, "Failed to find profile segment in DDP recipe.");
		return -EINVAL;
	}

	pinfo.track_id = track_id;
	pinfo.version = profile_hdr->version;
	if (is_add)
		pinfo.op = I40E_DDP_ADD_TRACKID;
	else
		pinfo.op = I40E_DDP_REMOVE_TRACKID;

	memcpy(pinfo.name, profile_hdr->name, I40E_DDP_NAME_SIZE);

	/* Check if profile data already exists*/
	istatus = i40e_ddp_does_profile_exist(&pf->hw, &pinfo);
	if (istatus < 0) {
		netdev_err(netdev, "Failed to fetch loaded profiles.");
		return istatus;
	}
	if (is_add) {
		if (istatus > 0) {
			netdev_err(netdev, "DDP profile already loaded.");
			return -EINVAL;
		}
		istatus = i40e_ddp_does_profile_overlap(&pf->hw, &pinfo);
		if (istatus < 0) {
			netdev_err(netdev, "Failed to fetch loaded profiles.");
			return istatus;
		}
		if (istatus > 0) {
			netdev_err(netdev, "DDP profile overlaps with existing one.");
			return -EINVAL;
		}
	} else {
		if (istatus == 0) {
			netdev_err(netdev,
				   "DDP profile for deletion does not exist.");
			return -EINVAL;
		}
	}

	/* Load profile data */
	if (is_add) {
		status = i40e_write_profile(&pf->hw, profile_hdr, track_id);
		if (status) {
			if (status == I40E_ERR_DEVICE_NOT_SUPPORTED) {
				netdev_err(netdev,
					   "Profile is not supported by the device.");
				return -EPERM;
			}
			netdev_err(netdev, "Failed to write DDP profile.");
			return -EIO;
		}
	} else {
		status = i40e_rollback_profile(&pf->hw, profile_hdr, track_id);
		if (status) {
			netdev_err(netdev, "Failed to remove DDP profile.");
			return -EIO;
		}
	}

	/* Add/remove profile to/from profile list in FW */
	if (is_add) {
		status = i40e_add_pinfo(&pf->hw, profile_hdr, profile_info_sec,
					track_id);
		if (status) {
			netdev_err(netdev, "Failed to add DDP profile info.");
			return -EIO;
		}
	} else {
		status = i40e_del_pinfo(&pf->hw, profile_hdr, profile_info_sec,
					track_id);
		if (status) {
			netdev_err(netdev, "Failed to restore DDP profile info.");
			return -EIO;
		}
	}

	return 0;
}