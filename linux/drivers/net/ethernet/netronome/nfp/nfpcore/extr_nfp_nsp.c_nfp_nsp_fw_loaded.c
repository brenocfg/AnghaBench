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
struct nfp_nsp_command_arg {int /*<<< orphan*/  code; } ;
struct nfp_nsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPCODE_FW_LOADED ; 
 int __nfp_nsp_command (struct nfp_nsp*,struct nfp_nsp_command_arg const*) ; 

int nfp_nsp_fw_loaded(struct nfp_nsp *state)
{
	const struct nfp_nsp_command_arg arg = {
		.code		= SPCODE_FW_LOADED,
	};

	return __nfp_nsp_command(state, &arg);
}