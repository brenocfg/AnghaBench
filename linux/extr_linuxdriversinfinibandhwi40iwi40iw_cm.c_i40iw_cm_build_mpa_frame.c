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
struct ietf_mpa_v2 {int dummy; } ;
struct ietf_mpa_v1 {int dummy; } ;
struct i40iw_kmem_info {int /*<<< orphan*/  addr; } ;
struct i40iw_cm_node {int mpa_frame_rev; } ;

/* Variables and functions */
#define  IETF_MPA_V1 129 
#define  IETF_MPA_V2 128 
 int /*<<< orphan*/  i40iw_build_mpa_v1 (struct i40iw_cm_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_build_mpa_v2 (struct i40iw_cm_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40iw_cm_build_mpa_frame(struct i40iw_cm_node *cm_node,
				    struct i40iw_kmem_info *mpa,
				    u8 mpa_key)
{
	int hdr_len = 0;

	switch (cm_node->mpa_frame_rev) {
	case IETF_MPA_V1:
		hdr_len = sizeof(struct ietf_mpa_v1);
		i40iw_build_mpa_v1(cm_node, mpa->addr, mpa_key);
		break;
	case IETF_MPA_V2:
		hdr_len = sizeof(struct ietf_mpa_v2);
		i40iw_build_mpa_v2(cm_node, mpa->addr, mpa_key);
		break;
	default:
		break;
	}

	return hdr_len;
}