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
typedef  int u32 ;
struct drm_psb_private {int dummy; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  PSB_CR_2D_BLIT_STATUS ; 
 int /*<<< orphan*/  PSB_CR_BIF_FAULT ; 
 int /*<<< orphan*/  PSB_CR_BIF_INT_STAT ; 
 int /*<<< orphan*/  PSB_CR_EVENT_HOST_CLEAR ; 
 int /*<<< orphan*/  PSB_CR_EVENT_HOST_CLEAR2 ; 
 int PSB_RSGX32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSB_WSGX32 (int,int /*<<< orphan*/ ) ; 
 int _PSB_CBI_STAT_FAULT_2D ; 
 int _PSB_CBI_STAT_FAULT_CACHE ; 
 int _PSB_CBI_STAT_FAULT_HOST ; 
 int _PSB_CBI_STAT_FAULT_ISP ; 
 int _PSB_CBI_STAT_FAULT_PBE ; 
 int _PSB_CBI_STAT_FAULT_TA ; 
 int _PSB_CBI_STAT_FAULT_TSP ; 
 int _PSB_CBI_STAT_FAULT_USSEPDS ; 
 int _PSB_CBI_STAT_FAULT_VDM ; 
 int _PSB_CBI_STAT_PF_N_RW ; 
 int _PSB_CE2_BIF_REQUESTER_FAULT ; 
 int _PSB_CE_TWOD_COMPLETE ; 

__attribute__((used)) static void psb_sgx_interrupt(struct drm_device *dev, u32 stat_1, u32 stat_2)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	u32 val, addr;
	int error = false;

	if (stat_1 & _PSB_CE_TWOD_COMPLETE)
		val = PSB_RSGX32(PSB_CR_2D_BLIT_STATUS);

	if (stat_2 & _PSB_CE2_BIF_REQUESTER_FAULT) {
		val = PSB_RSGX32(PSB_CR_BIF_INT_STAT);
		addr = PSB_RSGX32(PSB_CR_BIF_FAULT);
		if (val) {
			if (val & _PSB_CBI_STAT_PF_N_RW)
				DRM_ERROR("SGX MMU page fault:");
			else
				DRM_ERROR("SGX MMU read / write protection fault:");

			if (val & _PSB_CBI_STAT_FAULT_CACHE)
				DRM_ERROR("\tCache requestor");
			if (val & _PSB_CBI_STAT_FAULT_TA)
				DRM_ERROR("\tTA requestor");
			if (val & _PSB_CBI_STAT_FAULT_VDM)
				DRM_ERROR("\tVDM requestor");
			if (val & _PSB_CBI_STAT_FAULT_2D)
				DRM_ERROR("\t2D requestor");
			if (val & _PSB_CBI_STAT_FAULT_PBE)
				DRM_ERROR("\tPBE requestor");
			if (val & _PSB_CBI_STAT_FAULT_TSP)
				DRM_ERROR("\tTSP requestor");
			if (val & _PSB_CBI_STAT_FAULT_ISP)
				DRM_ERROR("\tISP requestor");
			if (val & _PSB_CBI_STAT_FAULT_USSEPDS)
				DRM_ERROR("\tUSSEPDS requestor");
			if (val & _PSB_CBI_STAT_FAULT_HOST)
				DRM_ERROR("\tHost requestor");

			DRM_ERROR("\tMMU failing address is 0x%08x.\n",
				  (unsigned int)addr);
			error = true;
		}
	}

	/* Clear bits */
	PSB_WSGX32(stat_1, PSB_CR_EVENT_HOST_CLEAR);
	PSB_WSGX32(stat_2, PSB_CR_EVENT_HOST_CLEAR2);
	PSB_RSGX32(PSB_CR_EVENT_HOST_CLEAR2);
}