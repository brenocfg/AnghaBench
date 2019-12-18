#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct geneve_sock {TYPE_2__* sock; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
struct TYPE_4__ {TYPE_1__* sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_family; } ;

/* Variables and functions */

__attribute__((used)) static sa_family_t geneve_get_sk_family(struct geneve_sock *gs)
{
	return gs->sock->sk->sk_family;
}