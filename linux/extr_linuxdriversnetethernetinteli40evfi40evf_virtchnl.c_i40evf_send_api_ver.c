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
typedef  int /*<<< orphan*/  vvi ;
typedef  int /*<<< orphan*/  u8 ;
struct virtchnl_version_info {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct i40evf_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTCHNL_OP_VERSION ; 
 int /*<<< orphan*/  VIRTCHNL_VERSION_MAJOR ; 
 int /*<<< orphan*/  VIRTCHNL_VERSION_MINOR ; 
 int i40evf_send_pf_msg (struct i40evf_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int i40evf_send_api_ver(struct i40evf_adapter *adapter)
{
	struct virtchnl_version_info vvi;

	vvi.major = VIRTCHNL_VERSION_MAJOR;
	vvi.minor = VIRTCHNL_VERSION_MINOR;

	return i40evf_send_pf_msg(adapter, VIRTCHNL_OP_VERSION, (u8 *)&vvi,
				  sizeof(vvi));
}