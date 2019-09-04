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
typedef  scalar_t__ u16 ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_CPP_ID (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nfp_cpp_interface (struct nfp_cpp*) ; 
 int nfp_cpp_mutex_validate (scalar_t__,int*,unsigned long long) ; 
 int nfp_cpp_readl (struct nfp_cpp*,int /*<<< orphan*/  const,unsigned long long,int /*<<< orphan*/ *) ; 
 int nfp_cpp_writel (struct nfp_cpp*,int /*<<< orphan*/  const,unsigned long long,int /*<<< orphan*/ ) ; 
 scalar_t__ nfp_mutex_is_unlocked (int /*<<< orphan*/ ) ; 
 scalar_t__ nfp_mutex_owner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_mutex_unlocked (scalar_t__) ; 

int nfp_cpp_mutex_reclaim(struct nfp_cpp *cpp, int target,
			  unsigned long long address)
{
	const u32 mur = NFP_CPP_ID(target, 3, 0);	/* atomic_read */
	const u32 muw = NFP_CPP_ID(target, 4, 0);	/* atomic_write */
	u16 interface = nfp_cpp_interface(cpp);
	int err;
	u32 tmp;

	err = nfp_cpp_mutex_validate(interface, &target, address);
	if (err)
		return err;

	/* Check lock */
	err = nfp_cpp_readl(cpp, mur, address, &tmp);
	if (err < 0)
		return err;

	if (nfp_mutex_is_unlocked(tmp) || nfp_mutex_owner(tmp) != interface)
		return 0;

	/* Bust the lock */
	err = nfp_cpp_writel(cpp, muw, address, nfp_mutex_unlocked(interface));
	if (err < 0)
		return err;

	return 1;
}