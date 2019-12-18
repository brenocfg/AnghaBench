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
struct dsa_switch {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_QDISC_TAPRIO 128 
 int sja1105_setup_tc_taprio (struct dsa_switch*,int,void*) ; 

__attribute__((used)) static int sja1105_port_setup_tc(struct dsa_switch *ds, int port,
				 enum tc_setup_type type,
				 void *type_data)
{
	switch (type) {
	case TC_SETUP_QDISC_TAPRIO:
		return sja1105_setup_tc_taprio(ds, port, type_data);
	default:
		return -EOPNOTSUPP;
	}
}