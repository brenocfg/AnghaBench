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
struct sock {int /*<<< orphan*/ * sk_prot; } ;

/* Variables and functions */
 int /*<<< orphan*/  chtls_cpl_prot ; 

void chtls_install_cpl_ops(struct sock *sk)
{
	sk->sk_prot = &chtls_cpl_prot;
}