#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uverbs_attr_bundle {int dummy; } ;
struct TYPE_2__ {size_t len; int /*<<< orphan*/  data; } ;
struct uverbs_attr {TYPE_1__ ptr_attr; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ clear_user (scalar_t__,size_t) ; 
 scalar_t__ u64_to_user_ptr (int /*<<< orphan*/ ) ; 
 struct uverbs_attr* uverbs_attr_get (struct uverbs_attr_bundle const*,size_t) ; 
 int uverbs_copy_to (struct uverbs_attr_bundle const*,size_t,void const*,size_t) ; 

int uverbs_copy_to_struct_or_zero(const struct uverbs_attr_bundle *bundle,
				  size_t idx, const void *from, size_t size)
{
	const struct uverbs_attr *attr = uverbs_attr_get(bundle, idx);

	if (size < attr->ptr_attr.len) {
		if (clear_user(u64_to_user_ptr(attr->ptr_attr.data) + size,
			       attr->ptr_attr.len - size))
			return -EFAULT;
	}
	return uverbs_copy_to(bundle, idx, from, size);
}