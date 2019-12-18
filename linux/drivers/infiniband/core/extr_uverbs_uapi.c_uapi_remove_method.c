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
struct uverbs_api {int dummy; } ;

/* Variables and functions */
 int UVERBS_API_ATTR_KEY_MASK ; 
 int /*<<< orphan*/  uapi_remove_range (struct uverbs_api*,int,int) ; 

__attribute__((used)) static void uapi_remove_method(struct uverbs_api *uapi, u32 method_key)
{
	uapi_remove_range(uapi, method_key,
			  method_key | UVERBS_API_ATTR_KEY_MASK);
}