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
struct nfp_nsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPCODE_ETH_CONTROL ; 
 int nfp_nsp_command_buf (struct nfp_nsp*,int /*<<< orphan*/ ,unsigned int,void const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int nfp_nsp_write_eth_table(struct nfp_nsp *state,
			    const void *buf, unsigned int size)
{
	return nfp_nsp_command_buf(state, SPCODE_ETH_CONTROL, size, buf, size,
				   NULL, 0);
}