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
typedef  union bfa_port_stats_u {int dummy; } bfa_port_stats_u ;
typedef  int /*<<< orphan*/  u32 ;
struct bfa_port_s {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_port_stats_swap(struct bfa_port_s *port, union bfa_port_stats_u *stats)
{
	u32    *dip = (u32 *) stats;
	__be32    t0, t1;
	int	    i;

	for (i = 0; i < sizeof(union bfa_port_stats_u)/sizeof(u32);
		i += 2) {
		t0 = dip[i];
		t1 = dip[i + 1];
#ifdef __BIG_ENDIAN
		dip[i] = be32_to_cpu(t0);
		dip[i + 1] = be32_to_cpu(t1);
#else
		dip[i] = be32_to_cpu(t1);
		dip[i + 1] = be32_to_cpu(t0);
#endif
	}
}