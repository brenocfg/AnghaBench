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
struct c4iw_ucontext {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  _c4iw_free_ucontext ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void c4iw_put_ucontext(struct c4iw_ucontext *ucontext)
{
	kref_put(&ucontext->kref, _c4iw_free_ucontext);
}