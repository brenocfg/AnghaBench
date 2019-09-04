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
typedef  int u16 ;
struct budget_patch {int dummy; } ;

/* Variables and functions */
 int COMTYPE_AUDIODAC ; 
 int OFF22K ; 
 int ON22K ; 
 int /*<<< orphan*/  budget_av7110_send_fw_cmd (struct budget_patch*,int*,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct budget_patch*) ; 

__attribute__((used)) static void av7110_set22k(struct budget_patch *budget, int state)
{
	u16 buf[2] = {( COMTYPE_AUDIODAC << 8) | (state ? ON22K : OFF22K), 0};

	dprintk(2, "budget: %p\n", budget);
	budget_av7110_send_fw_cmd(budget, buf, 2);
}