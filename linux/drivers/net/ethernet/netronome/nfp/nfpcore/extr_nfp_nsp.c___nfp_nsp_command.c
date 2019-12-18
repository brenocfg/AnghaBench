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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nfp_nsp_command_arg {int buf; int option; int code; int dma; int /*<<< orphan*/  (* error_cb ) (struct nfp_nsp*,int) ;int /*<<< orphan*/  error_quiet; scalar_t__ timeout_sec; } ;
struct nfp_nsp {int /*<<< orphan*/  res; struct nfp_cpp* cpp; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NFP_NSP_TIMEOUT_DEFAULT ; 
 int NSP_BUFFER ; 
 int NSP_COMMAND ; 
 int /*<<< orphan*/  NSP_COMMAND_CODE ; 
 int /*<<< orphan*/  NSP_COMMAND_DMA_BUF ; 
 int /*<<< orphan*/  NSP_COMMAND_OPTION ; 
 int /*<<< orphan*/  NSP_COMMAND_START ; 
 int NSP_STATUS ; 
 int /*<<< orphan*/  NSP_STATUS_BUSY ; 
 int /*<<< orphan*/  NSP_STATUS_RESULT ; 
 int nfp_cpp_readq (struct nfp_cpp*,int /*<<< orphan*/ ,int,int*) ; 
 int nfp_cpp_writeq (struct nfp_cpp*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*,int,int) ; 
 int nfp_nsp_check (struct nfp_nsp*) ; 
 int /*<<< orphan*/  nfp_nsp_print_extended_error (struct nfp_nsp*,int) ; 
 int nfp_nsp_wait_reg (struct nfp_cpp*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfp_resource_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_resource_cpp_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_warn (struct nfp_cpp*,char*,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct nfp_nsp*,int) ; 

__attribute__((used)) static int
__nfp_nsp_command(struct nfp_nsp *state, const struct nfp_nsp_command_arg *arg)
{
	u64 reg, ret_val, nsp_base, nsp_buffer, nsp_status, nsp_command;
	struct nfp_cpp *cpp = state->cpp;
	u32 nsp_cpp;
	int err;

	nsp_cpp = nfp_resource_cpp_id(state->res);
	nsp_base = nfp_resource_address(state->res);
	nsp_status = nsp_base + NSP_STATUS;
	nsp_command = nsp_base + NSP_COMMAND;
	nsp_buffer = nsp_base + NSP_BUFFER;

	err = nfp_nsp_check(state);
	if (err)
		return err;

	err = nfp_cpp_writeq(cpp, nsp_cpp, nsp_buffer, arg->buf);
	if (err < 0)
		return err;

	err = nfp_cpp_writeq(cpp, nsp_cpp, nsp_command,
			     FIELD_PREP(NSP_COMMAND_OPTION, arg->option) |
			     FIELD_PREP(NSP_COMMAND_CODE, arg->code) |
			     FIELD_PREP(NSP_COMMAND_DMA_BUF, arg->dma) |
			     FIELD_PREP(NSP_COMMAND_START, 1));
	if (err < 0)
		return err;

	/* Wait for NSP_COMMAND_START to go to 0 */
	err = nfp_nsp_wait_reg(cpp, &reg, nsp_cpp, nsp_command,
			       NSP_COMMAND_START, 0, NFP_NSP_TIMEOUT_DEFAULT);
	if (err) {
		nfp_err(cpp, "Error %d waiting for code 0x%04x to start\n",
			err, arg->code);
		return err;
	}

	/* Wait for NSP_STATUS_BUSY to go to 0 */
	err = nfp_nsp_wait_reg(cpp, &reg, nsp_cpp, nsp_status, NSP_STATUS_BUSY,
			       0, arg->timeout_sec ?: NFP_NSP_TIMEOUT_DEFAULT);
	if (err) {
		nfp_err(cpp, "Error %d waiting for code 0x%04x to complete\n",
			err, arg->code);
		return err;
	}

	err = nfp_cpp_readq(cpp, nsp_cpp, nsp_command, &ret_val);
	if (err < 0)
		return err;
	ret_val = FIELD_GET(NSP_COMMAND_OPTION, ret_val);

	err = FIELD_GET(NSP_STATUS_RESULT, reg);
	if (err) {
		if (!arg->error_quiet)
			nfp_warn(cpp, "Result (error) code set: %d (%d) command: %d\n",
				 -err, (int)ret_val, arg->code);

		if (arg->error_cb)
			arg->error_cb(state, ret_val);
		else
			nfp_nsp_print_extended_error(state, ret_val);
		return -err;
	}

	return ret_val;
}