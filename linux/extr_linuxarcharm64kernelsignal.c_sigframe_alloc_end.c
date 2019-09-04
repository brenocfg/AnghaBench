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
struct rt_sigframe_user_layout {int /*<<< orphan*/  size; int /*<<< orphan*/  limit; int /*<<< orphan*/  end_offset; } ;
struct _aarch64_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ TERMINATOR_SIZE ; 
 int sigframe_alloc (struct rt_sigframe_user_layout*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sigframe_alloc_end(struct rt_sigframe_user_layout *user)
{
	int ret;

	/* Un-reserve the space reserved for the terminator: */
	user->limit += TERMINATOR_SIZE;

	ret = sigframe_alloc(user, &user->end_offset,
			     sizeof(struct _aarch64_ctx));
	if (ret)
		return ret;

	/* Prevent further allocation: */
	user->limit = user->size;
	return 0;
}