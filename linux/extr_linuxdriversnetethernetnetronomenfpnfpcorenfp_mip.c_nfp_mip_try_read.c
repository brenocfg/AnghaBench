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
struct nfp_mip {scalar_t__ signature; scalar_t__ mip_version; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ NFP_MIP_SIGNATURE ; 
 scalar_t__ NFP_MIP_VERSION ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int nfp_cpp_read (struct nfp_cpp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_mip*,int) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*,int,int) ; 
 int /*<<< orphan*/  nfp_warn (struct nfp_cpp*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_mip_try_read(struct nfp_cpp *cpp, u32 cpp_id, u64 addr, struct nfp_mip *mip)
{
	int ret;

	ret = nfp_cpp_read(cpp, cpp_id, addr, mip, sizeof(*mip));
	if (ret != sizeof(*mip)) {
		nfp_err(cpp, "Failed to read MIP data (%d, %zu)\n",
			ret, sizeof(*mip));
		return -EIO;
	}
	if (mip->signature != NFP_MIP_SIGNATURE) {
		nfp_warn(cpp, "Incorrect MIP signature (0x%08x)\n",
			 le32_to_cpu(mip->signature));
		return -EINVAL;
	}
	if (mip->mip_version != NFP_MIP_VERSION) {
		nfp_warn(cpp, "Unsupported MIP version (%d)\n",
			 le32_to_cpu(mip->mip_version));
		return -EINVAL;
	}

	return 0;
}