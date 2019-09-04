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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct uverbs_attr_bundle {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ U32_MAX ; 
 int uverbs_get_flags64 (scalar_t__*,struct uverbs_attr_bundle const*,size_t,scalar_t__) ; 

int uverbs_get_flags32(u32 *to, const struct uverbs_attr_bundle *attrs_bundle,
		       size_t idx, u64 allowed_bits)
{
	u64 flags;
	int ret;

	ret = uverbs_get_flags64(&flags, attrs_bundle, idx, allowed_bits);
	if (ret)
		return ret;

	if (flags > U32_MAX)
		return -EINVAL;
	*to = flags;

	return 0;
}