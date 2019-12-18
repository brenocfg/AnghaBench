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
typedef  scalar_t__ u64 ;
struct uverbs_attr_bundle {int dummy; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct uverbs_attr {TYPE_1__ ptr_attr; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct uverbs_attr const*) ; 
 int PTR_ERR (struct uverbs_attr const*) ; 
 struct uverbs_attr* uverbs_attr_get (struct uverbs_attr_bundle const*,size_t) ; 

int _uverbs_get_const(s64 *to, const struct uverbs_attr_bundle *attrs_bundle,
		      size_t idx, s64 lower_bound, u64 upper_bound,
		      s64  *def_val)
{
	const struct uverbs_attr *attr;

	attr = uverbs_attr_get(attrs_bundle, idx);
	if (IS_ERR(attr)) {
		if ((PTR_ERR(attr) != -ENOENT) || !def_val)
			return PTR_ERR(attr);

		*to = *def_val;
	} else {
		*to = attr->ptr_attr.data;
	}

	if (*to < lower_bound || (*to > 0 && (u64)*to > upper_bound))
		return -EINVAL;

	return 0;
}