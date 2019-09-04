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
struct ib_ucontext {int dummy; } ;
struct c4iw_ucontext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_put_ucontext (struct c4iw_ucontext*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct ib_ucontext*) ; 
 struct c4iw_ucontext* to_c4iw_ucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int c4iw_dealloc_ucontext(struct ib_ucontext *context)
{
	struct c4iw_ucontext *ucontext = to_c4iw_ucontext(context);

	pr_debug("context %p\n", context);
	c4iw_put_ucontext(ucontext);
	return 0;
}