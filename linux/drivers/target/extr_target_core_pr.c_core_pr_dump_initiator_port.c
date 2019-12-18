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
struct t10_pr_registration {char* pr_reg_isid; int /*<<< orphan*/  isid_present_at_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

void core_pr_dump_initiator_port(
	struct t10_pr_registration *pr_reg,
	char *buf,
	u32 size)
{
	if (!pr_reg->isid_present_at_reg) {
		buf[0] = '\0';
		return;
	}

	snprintf(buf, size, ",i,0x%s", pr_reg->pr_reg_isid);
}