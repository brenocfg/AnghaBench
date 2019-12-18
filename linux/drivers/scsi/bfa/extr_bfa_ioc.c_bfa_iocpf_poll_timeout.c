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
struct bfa_ioc_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_ioc_poll_fwinit (struct bfa_ioc_s*) ; 

__attribute__((used)) static void
bfa_iocpf_poll_timeout(void *ioc_arg)
{
	struct bfa_ioc_s *ioc = (struct bfa_ioc_s *) ioc_arg;

	bfa_ioc_poll_fwinit(ioc);
}