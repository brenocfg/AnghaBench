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
typedef  int u8 ;
struct se_cmd {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int spc_modesense_rwrecovery(struct se_cmd *cmd, u8 pc, u8 *p)
{
	p[0] = 0x01;
	p[1] = 0x0a;

	/* No changeable values for now */
	if (pc == 1)
		goto out;

out:
	return 12;
}