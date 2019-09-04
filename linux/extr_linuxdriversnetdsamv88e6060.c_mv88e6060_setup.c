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

/* Variables and functions */
 int MV88E6060_PORTS ; 
 int mv88e6060_setup_addr (struct dsa_switch*) ; 
 int mv88e6060_setup_global (struct dsa_switch*) ; 
 int mv88e6060_setup_port (struct dsa_switch*,int) ; 
 int mv88e6060_switch_reset (struct dsa_switch*) ; 

__attribute__((used)) static int mv88e6060_setup(struct dsa_switch *ds)
{
	int ret;
	int i;

	ret = mv88e6060_switch_reset(ds);
	if (ret < 0)
		return ret;

	/* @@@ initialise atu */

	ret = mv88e6060_setup_global(ds);
	if (ret < 0)
		return ret;

	ret = mv88e6060_setup_addr(ds);
	if (ret < 0)
		return ret;

	for (i = 0; i < MV88E6060_PORTS; i++) {
		ret = mv88e6060_setup_port(ds, i);
		if (ret < 0)
			return ret;
	}

	return 0;
}