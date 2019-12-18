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
typedef  int u8 ;
typedef  int u32 ;
struct hdcp_srm_header {int srm_id; scalar_t__ reserved; int /*<<< orphan*/  srm_gen_no; int /*<<< orphan*/  srm_version; } ;
struct TYPE_2__ {int revoked_ksv_cnt; int /*<<< orphan*/  revoked_ksv_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_HDCP_2_DCP_SIG_SIZE ; 
 int const DRM_HDCP_2_KSV_COUNT_2_LSBITS (int const) ; 
 int /*<<< orphan*/  DRM_HDCP_2_NO_OF_DEV_PLUS_RESERVED_SZ ; 
 int DRM_HDCP_2_VRL_LENGTH_SIZE ; 
 int DRM_HDCP_KSV_LEN ; 
 int DRM_HDCP_SRM_ID_MASK ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int get_vrl_length (int const*) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 TYPE_1__* srm_data ; 

__attribute__((used)) static int drm_hdcp_parse_hdcp2_srm(const u8 *buf, size_t count)
{
	struct hdcp_srm_header *header;
	u32 vrl_length, ksv_count, ksv_sz;

	if (count < (sizeof(struct hdcp_srm_header) +
	    DRM_HDCP_2_VRL_LENGTH_SIZE + DRM_HDCP_2_DCP_SIG_SIZE)) {
		DRM_ERROR("Invalid blob length\n");
		return -EINVAL;
	}

	header = (struct hdcp_srm_header *)buf;
	DRM_DEBUG("SRM ID: 0x%x, SRM Ver: 0x%x, SRM Gen No: 0x%x\n",
		  header->srm_id & DRM_HDCP_SRM_ID_MASK,
		  be16_to_cpu(header->srm_version), header->srm_gen_no);

	if (header->reserved)
		return -EINVAL;

	buf = buf + sizeof(*header);
	vrl_length = get_vrl_length(buf);

	if (count < (sizeof(struct hdcp_srm_header) + vrl_length) ||
	    vrl_length < (DRM_HDCP_2_VRL_LENGTH_SIZE +
	    DRM_HDCP_2_DCP_SIG_SIZE)) {
		DRM_ERROR("Invalid blob length or vrl length\n");
		return -EINVAL;
	}

	/* Length of the all vrls combined */
	vrl_length -= (DRM_HDCP_2_VRL_LENGTH_SIZE +
		       DRM_HDCP_2_DCP_SIG_SIZE);

	if (!vrl_length) {
		DRM_ERROR("No vrl found\n");
		return -EINVAL;
	}

	buf += DRM_HDCP_2_VRL_LENGTH_SIZE;
	ksv_count = (*buf << 2) | DRM_HDCP_2_KSV_COUNT_2_LSBITS(*(buf + 1));
	if (!ksv_count) {
		DRM_DEBUG("Revoked KSV count is 0\n");
		return count;
	}

	kfree(srm_data->revoked_ksv_list);
	srm_data->revoked_ksv_list = kcalloc(ksv_count, DRM_HDCP_KSV_LEN,
					     GFP_KERNEL);
	if (!srm_data->revoked_ksv_list) {
		DRM_ERROR("Out of Memory\n");
		return -ENOMEM;
	}

	ksv_sz = ksv_count * DRM_HDCP_KSV_LEN;
	buf += DRM_HDCP_2_NO_OF_DEV_PLUS_RESERVED_SZ;

	DRM_DEBUG("Revoked KSVs: %d\n", ksv_count);
	memcpy(srm_data->revoked_ksv_list, buf, ksv_sz);

	srm_data->revoked_ksv_cnt = ksv_count;
	return count;
}