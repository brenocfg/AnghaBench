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
typedef  enum iwl_tof_range_request_status { ____Placeholder_iwl_tof_range_request_status } iwl_tof_range_request_status ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
#define  IWL_TOF_RANGE_REQUEST_STATUS_BUSY 129 
#define  IWL_TOF_RANGE_REQUEST_STATUS_SUCCESS 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static int
iwl_ftm_range_request_status_to_err(enum iwl_tof_range_request_status s)
{
	switch (s) {
	case IWL_TOF_RANGE_REQUEST_STATUS_SUCCESS:
		return 0;
	case IWL_TOF_RANGE_REQUEST_STATUS_BUSY:
		return -EBUSY;
	default:
		WARN_ON_ONCE(1);
		return -EIO;
	}
}