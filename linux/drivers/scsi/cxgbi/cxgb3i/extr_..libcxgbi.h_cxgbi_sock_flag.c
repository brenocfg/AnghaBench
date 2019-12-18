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
struct cxgbi_sock {int /*<<< orphan*/  flags; } ;
typedef  enum cxgbi_sock_flags { ____Placeholder_cxgbi_sock_flags } cxgbi_sock_flags ;

/* Variables and functions */
 int test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int cxgbi_sock_flag(struct cxgbi_sock *csk,
				enum cxgbi_sock_flags flag)
{
	if (csk == NULL)
		return 0;
	return test_bit(flag, &csk->flags);
}