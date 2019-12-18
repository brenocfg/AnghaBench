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
struct bfad_s {int /*<<< orphan*/  port_name; int /*<<< orphan*/  adapter_name; } ;
struct bfa_bsg_ioc_name_s {int /*<<< orphan*/  status; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 unsigned int IOCMD_IOC_SET_ADAPTER_NAME ; 
 unsigned int IOCMD_IOC_SET_PORT_NAME ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bfad_iocmd_ioc_set_name(struct bfad_s *bfad, void *cmd, unsigned int v_cmd)
{
	struct bfa_bsg_ioc_name_s *iocmd = (struct bfa_bsg_ioc_name_s *) cmd;

	if (v_cmd == IOCMD_IOC_SET_ADAPTER_NAME)
		strcpy(bfad->adapter_name, iocmd->name);
	else if (v_cmd == IOCMD_IOC_SET_PORT_NAME)
		strcpy(bfad->port_name, iocmd->name);

	iocmd->status = BFA_STATUS_OK;
	return 0;
}