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
struct tc_taprio_qopt_offload {int dummy; } ;
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static inline int sja1105_setup_tc_taprio(struct dsa_switch *ds, int port,
					  struct tc_taprio_qopt_offload *admin)
{
	return -EOPNOTSUPP;
}