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
struct ata_link {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SCR_CONTROL ; 
 int /*<<< orphan*/  uli_scr_cfg_write (struct ata_link*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uli_scr_write(struct ata_link *link, unsigned int sc_reg, u32 val)
{
	if (sc_reg > SCR_CONTROL) //SCR_CONTROL=2, SCR_ERROR=1, SCR_STATUS=0
		return -EINVAL;

	uli_scr_cfg_write(link, sc_reg, val);
	return 0;
}