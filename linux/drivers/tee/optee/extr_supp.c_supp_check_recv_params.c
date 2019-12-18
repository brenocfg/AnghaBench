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
struct TYPE_4__ {scalar_t__ shm; } ;
struct TYPE_3__ {TYPE_2__ memref; } ;
struct tee_param {scalar_t__ attr; TYPE_1__ u; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TEE_IOCTL_PARAM_ATTR_META ; 
 scalar_t__ tee_param_is_memref (struct tee_param*) ; 
 int /*<<< orphan*/  tee_shm_put (scalar_t__) ; 

__attribute__((used)) static int supp_check_recv_params(size_t num_params, struct tee_param *params,
				  size_t *num_meta)
{
	size_t n;

	if (!num_params)
		return -EINVAL;

	/*
	 * If there's memrefs we need to decrease those as they where
	 * increased earlier and we'll even refuse to accept any below.
	 */
	for (n = 0; n < num_params; n++)
		if (tee_param_is_memref(params + n) && params[n].u.memref.shm)
			tee_shm_put(params[n].u.memref.shm);

	/*
	 * We only expect parameters as TEE_IOCTL_PARAM_ATTR_TYPE_NONE with
	 * or without the TEE_IOCTL_PARAM_ATTR_META bit set.
	 */
	for (n = 0; n < num_params; n++)
		if (params[n].attr &&
		    params[n].attr != TEE_IOCTL_PARAM_ATTR_META)
			return -EINVAL;

	/* At most we'll need one meta parameter so no need to check for more */
	if (params->attr == TEE_IOCTL_PARAM_ATTR_META)
		*num_meta = 1;
	else
		*num_meta = 0;

	return 0;
}