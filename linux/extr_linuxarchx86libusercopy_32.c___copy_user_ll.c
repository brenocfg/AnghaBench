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

/* Variables and functions */
 int /*<<< orphan*/  __copy_user (void*,void const*,unsigned long) ; 
 unsigned long __copy_user_intel (void*,void const*,unsigned long) ; 
 int /*<<< orphan*/  __uaccess_begin_nospec () ; 
 int /*<<< orphan*/  __uaccess_end () ; 
 scalar_t__ movsl_is_ok (void*,void const*,unsigned long) ; 

unsigned long __copy_user_ll(void *to, const void *from, unsigned long n)
{
	__uaccess_begin_nospec();
	if (movsl_is_ok(to, from, n))
		__copy_user(to, from, n);
	else
		n = __copy_user_intel(to, from, n);
	__uaccess_end();
	return n;
}