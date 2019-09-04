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
struct qib_ibport {int dummy; } ;
struct ib_cc_mad {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int check_cc_key(struct qib_ibport *ibp,
			struct ib_cc_mad *ccp, int mad_flags)
{
	return 0;
}