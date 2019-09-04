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
struct delta_ipc_header_msg {int command; int /*<<< orphan*/  copro_hdl; int /*<<< orphan*/  host_hdl; int /*<<< orphan*/  tag; } ;
struct delta_ipc_ctx {int /*<<< orphan*/  copro_hdl; } ;
typedef  enum delta_ipc_fw_command { ____Placeholder_delta_ipc_fw_command } delta_ipc_fw_command ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_SANITY_TAG ; 
 int /*<<< orphan*/  to_host_hdl (struct delta_ipc_ctx*) ; 

__attribute__((used)) static void build_msg_header(struct delta_ipc_ctx *ctx,
			     enum delta_ipc_fw_command command,
			     struct delta_ipc_header_msg *header)
{
	header->tag = IPC_SANITY_TAG;
	header->host_hdl = to_host_hdl(ctx);
	header->copro_hdl = ctx->copro_hdl;
	header->command = command;
}