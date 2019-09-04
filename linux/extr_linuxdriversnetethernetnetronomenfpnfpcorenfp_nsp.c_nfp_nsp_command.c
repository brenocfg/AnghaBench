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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nfp_nsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NSP_TIMEOUT_DEFAULT ; 
 int __nfp_nsp_command (struct nfp_nsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_nsp_command(struct nfp_nsp *state, u16 code, u32 option, u32 buff_cpp,
		u64 buff_addr)
{
	return __nfp_nsp_command(state, code, option, buff_cpp, buff_addr,
				 NFP_NSP_TIMEOUT_DEFAULT);
}