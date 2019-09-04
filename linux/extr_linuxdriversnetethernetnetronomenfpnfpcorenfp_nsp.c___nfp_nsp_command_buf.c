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
typedef  unsigned int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int minor; unsigned int major; } ;
struct nfp_nsp {int /*<<< orphan*/  res; TYPE_1__ ver; struct nfp_cpp* cpp; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int FIELD_GET (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ NSP_DFLT_BUFFER ; 
 int /*<<< orphan*/  NSP_DFLT_BUFFER_ADDRESS ; 
 scalar_t__ NSP_DFLT_BUFFER_CONFIG ; 
 int /*<<< orphan*/  NSP_DFLT_BUFFER_CPP ; 
 int /*<<< orphan*/  NSP_DFLT_BUFFER_SIZE_MB ; 
 unsigned int SZ_1M ; 
 int __nfp_nsp_command (struct nfp_nsp*,int /*<<< orphan*/ ,int,int,unsigned int,int) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int nfp_cpp_read (struct nfp_cpp*,int,unsigned int,void*,unsigned int) ; 
 int nfp_cpp_readq (struct nfp_cpp*,int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 int nfp_cpp_write (struct nfp_cpp*,int,unsigned int,void*,unsigned int) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ nfp_resource_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_resource_cpp_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__nfp_nsp_command_buf(struct nfp_nsp *nsp, u16 code, u32 option,
		      const void *in_buf, unsigned int in_size, void *out_buf,
		      unsigned int out_size, u32 timeout_sec)
{
	struct nfp_cpp *cpp = nsp->cpp;
	unsigned int max_size;
	u64 reg, cpp_buf;
	int ret, err;
	u32 cpp_id;

	if (nsp->ver.minor < 13) {
		nfp_err(cpp, "NSP: Code 0x%04x with buffer not supported (ABI %hu.%hu)\n",
			code, nsp->ver.major, nsp->ver.minor);
		return -EOPNOTSUPP;
	}

	err = nfp_cpp_readq(cpp, nfp_resource_cpp_id(nsp->res),
			    nfp_resource_address(nsp->res) +
			    NSP_DFLT_BUFFER_CONFIG,
			    &reg);
	if (err < 0)
		return err;

	max_size = max(in_size, out_size);
	if (FIELD_GET(NSP_DFLT_BUFFER_SIZE_MB, reg) * SZ_1M < max_size) {
		nfp_err(cpp, "NSP: default buffer too small for command 0x%04x (%llu < %u)\n",
			code, FIELD_GET(NSP_DFLT_BUFFER_SIZE_MB, reg) * SZ_1M,
			max_size);
		return -EINVAL;
	}

	err = nfp_cpp_readq(cpp, nfp_resource_cpp_id(nsp->res),
			    nfp_resource_address(nsp->res) +
			    NSP_DFLT_BUFFER,
			    &reg);
	if (err < 0)
		return err;

	cpp_id = FIELD_GET(NSP_DFLT_BUFFER_CPP, reg) << 8;
	cpp_buf = FIELD_GET(NSP_DFLT_BUFFER_ADDRESS, reg);

	if (in_buf && in_size) {
		err = nfp_cpp_write(cpp, cpp_id, cpp_buf, in_buf, in_size);
		if (err < 0)
			return err;
	}
	/* Zero out remaining part of the buffer */
	if (out_buf && out_size && out_size > in_size) {
		memset(out_buf, 0, out_size - in_size);
		err = nfp_cpp_write(cpp, cpp_id, cpp_buf + in_size,
				    out_buf, out_size - in_size);
		if (err < 0)
			return err;
	}

	ret = __nfp_nsp_command(nsp, code, option, cpp_id, cpp_buf,
				timeout_sec);
	if (ret < 0)
		return ret;

	if (out_buf && out_size) {
		err = nfp_cpp_read(cpp, cpp_id, cpp_buf, out_buf, out_size);
		if (err < 0)
			return err;
	}

	return ret;
}