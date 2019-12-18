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
typedef  int /*<<< orphan*/  u8 ;
struct mei_hbm_cl_cmd {int /*<<< orphan*/  me_addr; int /*<<< orphan*/  host_addr; int /*<<< orphan*/  hbm_cmd; } ;
struct mei_cl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mei_cl_host_addr (struct mei_cl*) ; 
 int /*<<< orphan*/  mei_cl_me_id (struct mei_cl*) ; 
 int /*<<< orphan*/  memset (struct mei_hbm_cl_cmd*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline
void mei_hbm_cl_hdr(struct mei_cl *cl, u8 hbm_cmd, void *buf, size_t len)
{
	struct mei_hbm_cl_cmd *cmd = buf;

	memset(cmd, 0, len);

	cmd->hbm_cmd = hbm_cmd;
	cmd->host_addr = mei_cl_host_addr(cl);
	cmd->me_addr = mei_cl_me_id(cl);
}