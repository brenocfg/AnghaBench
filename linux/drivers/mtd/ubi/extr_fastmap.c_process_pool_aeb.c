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
struct ubi_vid_hdr {int /*<<< orphan*/  vol_id; } ;
struct ubi_device {int dummy; } ;
struct ubi_attach_info {int dummy; } ;
struct ubi_ainf_volume {int vol_id; } ;
struct ubi_ainf_peb {int dummy; } ;

/* Variables and functions */
 int UBI_BAD_FASTMAP ; 
 int UBI_FM_DATA_VOLUME_ID ; 
 int UBI_FM_SB_VOLUME_ID ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*) ; 
 struct ubi_ainf_volume* ubi_find_av (struct ubi_attach_info*,int) ; 
 int /*<<< orphan*/  ubi_free_aeb (struct ubi_attach_info*,struct ubi_ainf_peb*) ; 
 int update_vol (struct ubi_device*,struct ubi_attach_info*,struct ubi_ainf_volume*,struct ubi_vid_hdr*,struct ubi_ainf_peb*) ; 

__attribute__((used)) static int process_pool_aeb(struct ubi_device *ubi, struct ubi_attach_info *ai,
			    struct ubi_vid_hdr *new_vh,
			    struct ubi_ainf_peb *new_aeb)
{
	int vol_id = be32_to_cpu(new_vh->vol_id);
	struct ubi_ainf_volume *av;

	if (vol_id == UBI_FM_SB_VOLUME_ID || vol_id == UBI_FM_DATA_VOLUME_ID) {
		ubi_free_aeb(ai, new_aeb);

		return 0;
	}

	/* Find the volume this SEB belongs to */
	av = ubi_find_av(ai, vol_id);
	if (!av) {
		ubi_err(ubi, "orphaned volume in fastmap pool!");
		ubi_free_aeb(ai, new_aeb);
		return UBI_BAD_FASTMAP;
	}

	ubi_assert(vol_id == av->vol_id);

	return update_vol(ubi, ai, av, new_vh, new_aeb);
}