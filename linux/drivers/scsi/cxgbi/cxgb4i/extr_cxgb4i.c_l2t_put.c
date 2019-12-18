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
struct cxgbi_sock {int /*<<< orphan*/ * l2t; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb4_l2t_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 

__attribute__((used)) static inline void l2t_put(struct cxgbi_sock *csk)
{
	if (csk->l2t) {
		cxgb4_l2t_release(csk->l2t);
		csk->l2t = NULL;
		cxgbi_sock_put(csk);
	}
}