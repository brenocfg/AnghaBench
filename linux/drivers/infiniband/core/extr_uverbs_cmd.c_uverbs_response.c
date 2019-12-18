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
struct TYPE_2__ {size_t outlen; scalar_t__ outbuf; } ;
struct uverbs_attr_bundle {TYPE_1__ ucore; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  UVERBS_ATTR_CORE_OUT ; 
 int clear_user (scalar_t__,size_t) ; 
 scalar_t__ copy_to_user (scalar_t__,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (size_t,size_t) ; 
 scalar_t__ uverbs_attr_is_valid (struct uverbs_attr_bundle*,int /*<<< orphan*/ ) ; 
 int uverbs_copy_to_struct_or_zero (struct uverbs_attr_bundle*,int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int uverbs_response(struct uverbs_attr_bundle *attrs, const void *resp,
			   size_t resp_len)
{
	int ret;

	if (uverbs_attr_is_valid(attrs, UVERBS_ATTR_CORE_OUT))
		return uverbs_copy_to_struct_or_zero(
			attrs, UVERBS_ATTR_CORE_OUT, resp, resp_len);

	if (copy_to_user(attrs->ucore.outbuf, resp,
			 min(attrs->ucore.outlen, resp_len)))
		return -EFAULT;

	if (resp_len < attrs->ucore.outlen) {
		/*
		 * Zero fill any extra memory that user
		 * space might have provided.
		 */
		ret = clear_user(attrs->ucore.outbuf + resp_len,
				 attrs->ucore.outlen - resp_len);
		if (ret)
			return -EFAULT;
	}

	return 0;
}