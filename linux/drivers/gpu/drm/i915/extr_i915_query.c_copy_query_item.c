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
typedef  int u32 ;
struct drm_i915_query_item {scalar_t__ length; int /*<<< orphan*/  data_ptr; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_from_user (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int copy_query_item(void *query_hdr, size_t query_sz,
			   u32 total_length,
			   struct drm_i915_query_item *query_item)
{
	if (query_item->length == 0)
		return total_length;

	if (query_item->length < total_length)
		return -EINVAL;

	if (copy_from_user(query_hdr, u64_to_user_ptr(query_item->data_ptr),
			   query_sz))
		return -EFAULT;

	if (!access_ok(u64_to_user_ptr(query_item->data_ptr),
		       total_length))
		return -EFAULT;

	return 0;
}