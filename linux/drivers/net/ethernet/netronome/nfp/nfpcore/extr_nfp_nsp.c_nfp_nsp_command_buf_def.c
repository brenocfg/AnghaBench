#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int buf; } ;
struct nfp_nsp_command_buf_arg {int in_size; int out_size; int /*<<< orphan*/  out_buf; TYPE_1__ arg; int /*<<< orphan*/  in_buf; } ;
struct nfp_nsp {int /*<<< orphan*/  res; struct nfp_cpp* cpp; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FIELD_FIT (int /*<<< orphan*/ ,int) ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NSP_BUFFER_ADDRESS ; 
 int /*<<< orphan*/  NSP_BUFFER_CPP ; 
 scalar_t__ NSP_DFLT_BUFFER ; 
 int /*<<< orphan*/  NSP_DFLT_BUFFER_ADDRESS ; 
 int /*<<< orphan*/  NSP_DFLT_BUFFER_CPP ; 
 int __nfp_nsp_command (struct nfp_nsp*,TYPE_1__*) ; 
 int nfp_cpp_read (struct nfp_cpp*,int,int,int /*<<< orphan*/ ,int) ; 
 int nfp_cpp_readq (struct nfp_cpp*,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int nfp_cpp_write (struct nfp_cpp*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*,int,int) ; 
 scalar_t__ nfp_resource_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_resource_cpp_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_nsp_command_buf_def(struct nfp_nsp *nsp,
			struct nfp_nsp_command_buf_arg *arg)
{
	struct nfp_cpp *cpp = nsp->cpp;
	u64 reg, cpp_buf;
	int err, ret;
	u32 cpp_id;

	err = nfp_cpp_readq(cpp, nfp_resource_cpp_id(nsp->res),
			    nfp_resource_address(nsp->res) +
			    NSP_DFLT_BUFFER,
			    &reg);
	if (err < 0)
		return err;

	cpp_id = FIELD_GET(NSP_DFLT_BUFFER_CPP, reg) << 8;
	cpp_buf = FIELD_GET(NSP_DFLT_BUFFER_ADDRESS, reg);

	if (arg->in_buf && arg->in_size) {
		err = nfp_cpp_write(cpp, cpp_id, cpp_buf,
				    arg->in_buf, arg->in_size);
		if (err < 0)
			return err;
	}
	/* Zero out remaining part of the buffer */
	if (arg->out_buf && arg->out_size && arg->out_size > arg->in_size) {
		err = nfp_cpp_write(cpp, cpp_id, cpp_buf + arg->in_size,
				    arg->out_buf, arg->out_size - arg->in_size);
		if (err < 0)
			return err;
	}

	if (!FIELD_FIT(NSP_BUFFER_CPP, cpp_id >> 8) ||
	    !FIELD_FIT(NSP_BUFFER_ADDRESS, cpp_buf)) {
		nfp_err(cpp, "Buffer out of reach %08x %016llx\n",
			cpp_id, cpp_buf);
		return -EINVAL;
	}

	arg->arg.buf = FIELD_PREP(NSP_BUFFER_CPP, cpp_id >> 8) |
		       FIELD_PREP(NSP_BUFFER_ADDRESS, cpp_buf);
	ret = __nfp_nsp_command(nsp, &arg->arg);
	if (ret < 0)
		return ret;

	if (arg->out_buf && arg->out_size) {
		err = nfp_cpp_read(cpp, cpp_id, cpp_buf,
				   arg->out_buf, arg->out_size);
		if (err < 0)
			return err;
	}

	return ret;
}