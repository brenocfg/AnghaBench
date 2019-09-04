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
struct kvmppc_vcore {int /*<<< orphan*/  halt_poll_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  halt_poll_ns_shrink ; 

__attribute__((used)) static void shrink_halt_poll_ns(struct kvmppc_vcore *vc)
{
	if (halt_poll_ns_shrink == 0)
		vc->halt_poll_ns = 0;
	else
		vc->halt_poll_ns /= halt_poll_ns_shrink;
}