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
struct isac_hw {int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IPAC_TYPE_ISACX ; 
 int /*<<< orphan*/  ISACX_CIX0 ; 
 int /*<<< orphan*/  ISAC_CIX0 ; 
 int /*<<< orphan*/  WriteISAC (struct isac_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
ph_command(struct isac_hw *isac, u8 command)
{
	pr_debug("%s: ph_command %x\n", isac->name, command);
	if (isac->type & IPAC_TYPE_ISACX)
		WriteISAC(isac, ISACX_CIX0, (command << 4) | 0xE);
	else
		WriteISAC(isac, ISAC_CIX0, (command << 2) | 3);
}