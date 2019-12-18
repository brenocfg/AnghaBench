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
struct qm_fd {scalar_t__ cfg; scalar_t__ cmd; } ;

/* Variables and functions */
 scalar_t__ qm_fd_addr_get64 (struct qm_fd const*) ; 
 scalar_t__ qm_fd_get_format (struct qm_fd const*) ; 

__attribute__((used)) static bool fd_neq(const struct qm_fd *a, const struct qm_fd *b)
{
	bool neq = qm_fd_addr_get64(a) != qm_fd_addr_get64(b);

	neq |= qm_fd_get_format(a) != qm_fd_get_format(b);
	neq |= a->cfg != b->cfg;
	neq |= a->cmd != b->cmd;

	return neq;
}