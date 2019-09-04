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
struct ib_qp_security {struct ib_qp_security* ports_pkeys; int /*<<< orphan*/  security; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ib_qp_security*) ; 
 int /*<<< orphan*/  security_ib_free_security (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_qp_security(struct ib_qp_security *sec)
{
	security_ib_free_security(sec->security);
	kfree(sec->ports_pkeys);
	kfree(sec);
}