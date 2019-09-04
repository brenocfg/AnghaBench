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
typedef  int /*<<< orphan*/  uint8_t ;
struct ishtp_hbm_cl_cmd {int /*<<< orphan*/  fw_addr; int /*<<< orphan*/  host_addr; int /*<<< orphan*/  hbm_cmd; } ;
struct ishtp_cl {int /*<<< orphan*/  fw_client_id; int /*<<< orphan*/  host_client_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ishtp_hbm_cl_cmd*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void ishtp_hbm_cl_hdr(struct ishtp_cl *cl, uint8_t hbm_cmd,
	void *buf, size_t len)
{
	struct ishtp_hbm_cl_cmd *cmd = buf;

	memset(cmd, 0, len);

	cmd->hbm_cmd = hbm_cmd;
	cmd->host_addr = cl->host_client_id;
	cmd->fw_addr = cl->fw_client_id;
}