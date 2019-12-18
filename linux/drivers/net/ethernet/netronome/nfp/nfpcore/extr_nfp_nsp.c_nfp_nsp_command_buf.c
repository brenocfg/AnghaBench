#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
struct nfp_nsp_command_buf_arg {scalar_t__ out_size; scalar_t__ in_size; TYPE_2__ arg; scalar_t__ out_buf; } ;
struct TYPE_3__ {int minor; unsigned int major; } ;
struct nfp_nsp {int /*<<< orphan*/  res; TYPE_1__ ver; struct nfp_cpp* cpp; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 unsigned int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NSP_DFLT_BUFFER_CONFIG ; 
 int /*<<< orphan*/  NSP_DFLT_BUFFER_DMA_CHUNK_ORDER ; 
 int /*<<< orphan*/  NSP_DFLT_BUFFER_SIZE_4KB ; 
 int /*<<< orphan*/  NSP_DFLT_BUFFER_SIZE_MB ; 
 unsigned int SZ_1M ; 
 unsigned int SZ_4K ; 
 unsigned int max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int nfp_cpp_readq (struct nfp_cpp*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int nfp_nsp_command_buf_def (struct nfp_nsp*,struct nfp_nsp_command_buf_arg*) ; 
 int nfp_nsp_command_buf_dma (struct nfp_nsp*,struct nfp_nsp_command_buf_arg*,unsigned int,unsigned int) ; 
 scalar_t__ nfp_resource_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_resource_cpp_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_nsp_command_buf(struct nfp_nsp *nsp, struct nfp_nsp_command_buf_arg *arg)
{
	unsigned int dma_order, def_size, max_size;
	struct nfp_cpp *cpp = nsp->cpp;
	u64 reg;
	int err;

	if (nsp->ver.minor < 13) {
		nfp_err(cpp, "NSP: Code 0x%04x with buffer not supported (ABI %hu.%hu)\n",
			arg->arg.code, nsp->ver.major, nsp->ver.minor);
		return -EOPNOTSUPP;
	}

	err = nfp_cpp_readq(cpp, nfp_resource_cpp_id(nsp->res),
			    nfp_resource_address(nsp->res) +
			    NSP_DFLT_BUFFER_CONFIG,
			    &reg);
	if (err < 0)
		return err;

	/* Zero out undefined part of the out buffer */
	if (arg->out_buf && arg->out_size && arg->out_size > arg->in_size)
		memset(arg->out_buf, 0, arg->out_size - arg->in_size);

	max_size = max(arg->in_size, arg->out_size);
	def_size = FIELD_GET(NSP_DFLT_BUFFER_SIZE_MB, reg) * SZ_1M +
		   FIELD_GET(NSP_DFLT_BUFFER_SIZE_4KB, reg) * SZ_4K;
	dma_order = FIELD_GET(NSP_DFLT_BUFFER_DMA_CHUNK_ORDER, reg);
	if (def_size >= max_size) {
		return nfp_nsp_command_buf_def(nsp, arg);
	} else if (!dma_order) {
		nfp_err(cpp, "NSP: default buffer too small for command 0x%04x (%u < %u)\n",
			arg->arg.code, def_size, max_size);
		return -EINVAL;
	}

	return nfp_nsp_command_buf_dma(nsp, arg, max_size, dma_order);
}