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
typedef  int /*<<< orphan*/  u64 ;
struct nvif_device {int /*<<< orphan*/  object; } ;
struct nv_device_time_v0 {int /*<<< orphan*/  time; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEVICE_V0_TIME ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int nvif_object_mthd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nv_device_time_v0*,int) ; 

u64
nvif_device_time(struct nvif_device *device)
{
	struct nv_device_time_v0 args = {};
	int ret = nvif_object_mthd(&device->object, NV_DEVICE_V0_TIME,
				   &args, sizeof(args));
	WARN_ON_ONCE(ret != 0);
	return args.time;
}