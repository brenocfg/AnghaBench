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
struct firedtv_tuner_status {int ca_module_present_status; int ca_initialization_status; scalar_t__ ca_error_flag; int ca_dvb_flag; } ;

/* Variables and functions */
 int CA_CI_MODULE_PRESENT ; 
 int CA_CI_MODULE_READY ; 

__attribute__((used)) static int fdtv_get_ca_flags(struct firedtv_tuner_status *stat)
{
	int flags = 0;

	if (stat->ca_module_present_status == 1)
		flags |= CA_CI_MODULE_PRESENT;
	if (stat->ca_initialization_status == 1 &&
	    stat->ca_error_flag            == 0 &&
	    stat->ca_dvb_flag              == 1)
		flags |= CA_CI_MODULE_READY;
	return flags;
}