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
typedef  int /*<<< orphan*/  u16 ;
struct uverbs_api_object {int dummy; } ;
struct uverbs_api {int /*<<< orphan*/  radix; } ;

/* Variables and functions */
 struct uverbs_api_object const* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uapi_key_obj (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const struct uverbs_api_object *
uapi_get_object(struct uverbs_api *uapi, u16 object_id)
{
	return radix_tree_lookup(&uapi->radix, uapi_key_obj(object_id));
}