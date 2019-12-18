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
struct uverbs_api {int /*<<< orphan*/  radix; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 scalar_t__ WARN_ON (int) ; 
 void* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* uapi_add_elm (struct uverbs_api*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void *uapi_add_get_elm(struct uverbs_api *uapi, u32 key,
			      size_t alloc_size, bool *exists)
{
	void *elm;

	elm = uapi_add_elm(uapi, key, alloc_size);
	if (!IS_ERR(elm)) {
		*exists = false;
		return elm;
	}

	if (elm != ERR_PTR(-EEXIST))
		return elm;

	elm = radix_tree_lookup(&uapi->radix, key);
	if (WARN_ON(!elm))
		return ERR_PTR(-EINVAL);
	*exists = true;
	return elm;
}