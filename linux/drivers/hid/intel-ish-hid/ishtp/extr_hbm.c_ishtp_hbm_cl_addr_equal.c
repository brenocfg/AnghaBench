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
struct ishtp_hbm_cl_cmd {scalar_t__ host_addr; scalar_t__ fw_addr; } ;
struct ishtp_cl {scalar_t__ host_client_id; scalar_t__ fw_client_id; } ;

/* Variables and functions */

__attribute__((used)) static inline bool ishtp_hbm_cl_addr_equal(struct ishtp_cl *cl, void *buf)
{
	struct ishtp_hbm_cl_cmd *cmd = buf;

	return cl->host_client_id == cmd->host_addr &&
		cl->fw_client_id == cmd->fw_addr;
}