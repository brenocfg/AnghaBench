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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nfp_nsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NSP_TIMEOUT_DEFAULT ; 
 int __nfp_nsp_command_buf (struct nfp_nsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,unsigned int,void*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_nsp_command_buf(struct nfp_nsp *nsp, u16 code, u32 option,
		    const void *in_buf, unsigned int in_size, void *out_buf,
		    unsigned int out_size)
{
	return __nfp_nsp_command_buf(nsp, code, option, in_buf, in_size,
				     out_buf, out_size,
				     NFP_NSP_TIMEOUT_DEFAULT);
}