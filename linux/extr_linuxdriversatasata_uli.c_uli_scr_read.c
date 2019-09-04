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
 int /*<<< orphan*/  uli_scr_cfg_read (struct ata_link*,unsigned int) ; 

__attribute__((used)) static int uli_scr_read(struct ata_link *link, unsigned int sc_reg, u32 *val)
{
	if (sc_reg > SCR_CONTROL)
		return -EINVAL;

	*val = uli_scr_cfg_read(link, sc_reg);
	return 0;
}