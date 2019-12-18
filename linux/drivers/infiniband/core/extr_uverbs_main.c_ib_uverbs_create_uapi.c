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
struct uverbs_api {int dummy; } ;
struct ib_uverbs_device {struct uverbs_api* uapi; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct uverbs_api*) ; 
 int PTR_ERR (struct uverbs_api*) ; 
 struct uverbs_api* uverbs_alloc_api (struct ib_device*) ; 

__attribute__((used)) static int ib_uverbs_create_uapi(struct ib_device *device,
				 struct ib_uverbs_device *uverbs_dev)
{
	struct uverbs_api *uapi;

	uapi = uverbs_alloc_api(device);
	if (IS_ERR(uapi))
		return PTR_ERR(uapi);

	uverbs_dev->uapi = uapi;
	return 0;
}