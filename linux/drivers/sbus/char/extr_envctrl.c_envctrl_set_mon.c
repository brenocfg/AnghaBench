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
struct i2c_child_t {int /*<<< orphan*/ * mon_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVCTRL_CPUTEMP_MON ; 
 int /*<<< orphan*/  ENVCTRL_CPUVOLTAGE_MON ; 
 int /*<<< orphan*/  ENVCTRL_ETHERTEMP_MON ; 
 int /*<<< orphan*/  ENVCTRL_MTHRBDTEMP_MON ; 
 int /*<<< orphan*/  ENVCTRL_SCSITEMP_MON ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void envctrl_set_mon(struct i2c_child_t *pchild,
			    const char *chnl_desc,
			    int chnl_no)
{
	/* Firmware only has temperature type.  It does not distinguish
	 * different kinds of temperatures.  We use channel description
	 * to disinguish them.
	 */
	if (!(strcmp(chnl_desc,"temp,cpu")) ||
	    !(strcmp(chnl_desc,"temp,cpu0")) ||
	    !(strcmp(chnl_desc,"temp,cpu1")) ||
	    !(strcmp(chnl_desc,"temp,cpu2")) ||
	    !(strcmp(chnl_desc,"temp,cpu3")))
		pchild->mon_type[chnl_no] = ENVCTRL_CPUTEMP_MON;

	if (!(strcmp(chnl_desc,"vddcore,cpu0")) ||
	    !(strcmp(chnl_desc,"vddcore,cpu1")) ||
	    !(strcmp(chnl_desc,"vddcore,cpu2")) ||
	    !(strcmp(chnl_desc,"vddcore,cpu3")))
		pchild->mon_type[chnl_no] = ENVCTRL_CPUVOLTAGE_MON;

	if (!(strcmp(chnl_desc,"temp,motherboard")))
		pchild->mon_type[chnl_no] = ENVCTRL_MTHRBDTEMP_MON;

	if (!(strcmp(chnl_desc,"temp,scsi")))
		pchild->mon_type[chnl_no] = ENVCTRL_SCSITEMP_MON;

	if (!(strcmp(chnl_desc,"temp,ethernet")))
		pchild->mon_type[chnl_no] = ENVCTRL_ETHERTEMP_MON;
}