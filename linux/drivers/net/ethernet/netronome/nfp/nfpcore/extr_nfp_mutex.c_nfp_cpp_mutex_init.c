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
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_CPP_ID (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_cpp_interface (struct nfp_cpp*) ; 
 int nfp_cpp_mutex_validate (int /*<<< orphan*/ ,int*,unsigned long long) ; 
 int nfp_cpp_writel (struct nfp_cpp*,int /*<<< orphan*/  const,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_mutex_locked (int /*<<< orphan*/ ) ; 

int nfp_cpp_mutex_init(struct nfp_cpp *cpp,
		       int target, unsigned long long address, u32 key)
{
	const u32 muw = NFP_CPP_ID(target, 4, 0);    /* atomic_write */
	u16 interface = nfp_cpp_interface(cpp);
	int err;

	err = nfp_cpp_mutex_validate(interface, &target, address);
	if (err)
		return err;

	err = nfp_cpp_writel(cpp, muw, address + 4, key);
	if (err)
		return err;

	err = nfp_cpp_writel(cpp, muw, address, nfp_mutex_locked(interface));
	if (err)
		return err;

	return 0;
}