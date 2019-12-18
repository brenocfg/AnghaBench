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
typedef  int /*<<< orphan*/  u32 ;
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_admin_set_features ; 
 int nvme_features (struct nvme_ctrl*,int /*<<< orphan*/ ,unsigned int,unsigned int,void*,size_t,int /*<<< orphan*/ *) ; 

int nvme_set_features(struct nvme_ctrl *dev, unsigned int fid,
		      unsigned int dword11, void *buffer, size_t buflen,
		      u32 *result)
{
	return nvme_features(dev, nvme_admin_set_features, fid, dword11, buffer,
			     buflen, result);
}