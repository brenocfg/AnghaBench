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
typedef  int u16 ;
typedef  int /*<<< orphan*/  tmp_nodenum ;
struct pnp_bios_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNP_DS ; 
 int PNP_FUNCTION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  PNP_GET_SYS_DEV_NODE ; 
 int /*<<< orphan*/  PNP_TS1 ; 
 int /*<<< orphan*/  PNP_TS2 ; 
 int call_pnp_bios (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,struct pnp_bios_node*,int) ; 
 int /*<<< orphan*/  pnp_bios_present () ; 
 scalar_t__ pnpbios_dont_use_current_config ; 

__attribute__((used)) static int __pnp_bios_get_dev_node(u8 *nodenum, char boot,
				   struct pnp_bios_node *data)
{
	u16 status;
	u16 tmp_nodenum;

	if (!pnp_bios_present())
		return PNP_FUNCTION_NOT_SUPPORTED;
	if (!boot && pnpbios_dont_use_current_config)
		return PNP_FUNCTION_NOT_SUPPORTED;
	tmp_nodenum = *nodenum;
	status = call_pnp_bios(PNP_GET_SYS_DEV_NODE, 0, PNP_TS1, 0, PNP_TS2,
			       boot ? 2 : 1, PNP_DS, 0, &tmp_nodenum,
			       sizeof(tmp_nodenum), data, 65536);
	*nodenum = tmp_nodenum;
	return status;
}