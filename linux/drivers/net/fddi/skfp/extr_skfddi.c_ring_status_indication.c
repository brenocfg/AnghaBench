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
typedef  int u_long ;
struct s_smc {int dummy; } ;

/* Variables and functions */
 int RS_BEACON ; 
 int RS_DISCONNECT ; 
 int RS_DUPADDR ; 
 int RS_EVENT ; 
 int RS_HARDERROR ; 
 int RS_NORINGOP ; 
 int RS_PATHTEST ; 
 int RS_RES0 ; 
 int RS_RES15 ; 
 int RS_RES7 ; 
 int RS_RES9 ; 
 int RS_RINGOPCHANGE ; 
 int RS_SELFTEST ; 
 int RS_SOFTERROR ; 
 int RS_STUCKBYPASSS ; 
 int RS_VERSION ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

void ring_status_indication(struct s_smc *smc, u_long status)
{
	pr_debug("ring_status_indication( ");
	if (status & RS_RES15)
		pr_debug("RS_RES15 ");
	if (status & RS_HARDERROR)
		pr_debug("RS_HARDERROR ");
	if (status & RS_SOFTERROR)
		pr_debug("RS_SOFTERROR ");
	if (status & RS_BEACON)
		pr_debug("RS_BEACON ");
	if (status & RS_PATHTEST)
		pr_debug("RS_PATHTEST ");
	if (status & RS_SELFTEST)
		pr_debug("RS_SELFTEST ");
	if (status & RS_RES9)
		pr_debug("RS_RES9 ");
	if (status & RS_DISCONNECT)
		pr_debug("RS_DISCONNECT ");
	if (status & RS_RES7)
		pr_debug("RS_RES7 ");
	if (status & RS_DUPADDR)
		pr_debug("RS_DUPADDR ");
	if (status & RS_NORINGOP)
		pr_debug("RS_NORINGOP ");
	if (status & RS_VERSION)
		pr_debug("RS_VERSION ");
	if (status & RS_STUCKBYPASSS)
		pr_debug("RS_STUCKBYPASSS ");
	if (status & RS_EVENT)
		pr_debug("RS_EVENT ");
	if (status & RS_RINGOPCHANGE)
		pr_debug("RS_RINGOPCHANGE ");
	if (status & RS_RES0)
		pr_debug("RS_RES0 ");
	pr_debug("]\n");
}