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
typedef  int /*<<< orphan*/  u32 ;
struct bfa_qos_stats_s {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcport_qos_stats_swap(struct bfa_qos_stats_s *d,
	struct bfa_qos_stats_s *s)
{
	u32	*dip = (u32 *) d;
	__be32	*sip = (__be32 *) s;
	int		i;

	/* Now swap the 32 bit fields */
	for (i = 0; i < (sizeof(struct bfa_qos_stats_s)/sizeof(u32)); ++i)
		dip[i] = be32_to_cpu(sip[i]);
}