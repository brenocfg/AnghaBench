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
struct iavf_hw {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IAVF_VFGEN_RSTAT ; 
 int IAVF_VFGEN_RSTAT_VFR_STATE_MASK ; 
 int VIRTCHNL_VFR_COMPLETED ; 
 int VIRTCHNL_VFR_VFACTIVE ; 
 int rd32 (struct iavf_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int iavf_check_reset_complete(struct iavf_hw *hw)
{
	u32 rstat;
	int i;

	for (i = 0; i < 100; i++) {
		rstat = rd32(hw, IAVF_VFGEN_RSTAT) &
			     IAVF_VFGEN_RSTAT_VFR_STATE_MASK;
		if ((rstat == VIRTCHNL_VFR_VFACTIVE) ||
		    (rstat == VIRTCHNL_VFR_COMPLETED))
			return 0;
		usleep_range(10, 20);
	}
	return -EBUSY;
}