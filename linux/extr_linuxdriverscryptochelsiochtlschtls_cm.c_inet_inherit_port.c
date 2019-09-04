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
struct sock {int dummy; } ;
struct inet_hashinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __inet_inherit_port (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 

__attribute__((used)) static void inet_inherit_port(struct inet_hashinfo *hash_info,
			      struct sock *lsk, struct sock *newsk)
{
	local_bh_disable();
	__inet_inherit_port(lsk, newsk);
	local_bh_enable();
}