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
typedef  size_t uint32_t ;
struct amdgpu_iv_entry {int client_id; int src_id; int /*<<< orphan*/ * src_data; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_4__ {TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_2__ vcn; } ;
struct TYPE_3__ {int /*<<< orphan*/  ring_jpeg; int /*<<< orphan*/ * ring_enc; int /*<<< orphan*/  ring_dec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
#define  SOC15_IH_CLIENTID_VCN 133 
#define  SOC15_IH_CLIENTID_VCN1 132 
#define  VCN_2_0__SRCID__JPEG_DECODE 131 
#define  VCN_2_0__SRCID__UVD_ENC_GENERAL_PURPOSE 130 
#define  VCN_2_0__SRCID__UVD_ENC_LOW_LATENCY 129 
#define  VCN_2_0__SRCID__UVD_SYSTEM_MESSAGE_INTERRUPT 128 
 int /*<<< orphan*/  amdgpu_fence_process (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vcn_v2_5_process_interrupt(struct amdgpu_device *adev,
				      struct amdgpu_irq_src *source,
				      struct amdgpu_iv_entry *entry)
{
	uint32_t ip_instance;

	switch (entry->client_id) {
	case SOC15_IH_CLIENTID_VCN:
		ip_instance = 0;
		break;
	case SOC15_IH_CLIENTID_VCN1:
		ip_instance = 1;
		break;
	default:
		DRM_ERROR("Unhandled client id: %d\n", entry->client_id);
		return 0;
	}

	DRM_DEBUG("IH: VCN TRAP\n");

	switch (entry->src_id) {
	case VCN_2_0__SRCID__UVD_SYSTEM_MESSAGE_INTERRUPT:
		amdgpu_fence_process(&adev->vcn.inst[ip_instance].ring_dec);
		break;
	case VCN_2_0__SRCID__UVD_ENC_GENERAL_PURPOSE:
		amdgpu_fence_process(&adev->vcn.inst[ip_instance].ring_enc[0]);
		break;
	case VCN_2_0__SRCID__UVD_ENC_LOW_LATENCY:
		amdgpu_fence_process(&adev->vcn.inst[ip_instance].ring_enc[1]);
		break;
	case VCN_2_0__SRCID__JPEG_DECODE:
		amdgpu_fence_process(&adev->vcn.inst[ip_instance].ring_jpeg);
		break;
	default:
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);
		break;
	}

	return 0;
}