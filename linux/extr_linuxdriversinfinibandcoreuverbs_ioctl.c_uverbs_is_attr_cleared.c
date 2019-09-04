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
typedef  int u16 ;
struct ib_uverbs_attr {int len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ib_is_buffer_cleared (int,int) ; 
 int /*<<< orphan*/  memchr_inv (void const*,int /*<<< orphan*/ ,int) ; 
 int u64_to_user_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool uverbs_is_attr_cleared(const struct ib_uverbs_attr *uattr,
				   u16 len)
{
	if (uattr->len > sizeof(((struct ib_uverbs_attr *)0)->data))
		return ib_is_buffer_cleared(u64_to_user_ptr(uattr->data) + len,
					    uattr->len - len);

	return !memchr_inv((const void *)&uattr->data + len,
			   0, uattr->len - len);
}