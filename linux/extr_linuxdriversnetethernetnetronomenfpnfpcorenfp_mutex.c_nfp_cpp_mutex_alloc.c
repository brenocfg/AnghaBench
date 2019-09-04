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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nfp_cpp_mutex {int target; unsigned long long address; scalar_t__ depth; scalar_t__ key; struct nfp_cpp* cpp; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NFP_CPP_ID (int,int,int /*<<< orphan*/ ) ; 
 struct nfp_cpp_mutex* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_cpp_interface (struct nfp_cpp*) ; 
 int nfp_cpp_mutex_validate (int /*<<< orphan*/ ,int*,unsigned long long) ; 
 int nfp_cpp_readl (struct nfp_cpp*,scalar_t__ const,unsigned long long,scalar_t__*) ; 

struct nfp_cpp_mutex *nfp_cpp_mutex_alloc(struct nfp_cpp *cpp, int target,
					  unsigned long long address, u32 key)
{
	const u32 mur = NFP_CPP_ID(target, 3, 0);    /* atomic_read */
	u16 interface = nfp_cpp_interface(cpp);
	struct nfp_cpp_mutex *mutex;
	int err;
	u32 tmp;

	err = nfp_cpp_mutex_validate(interface, &target, address);
	if (err)
		return NULL;

	err = nfp_cpp_readl(cpp, mur, address + 4, &tmp);
	if (err < 0)
		return NULL;

	if (tmp != key)
		return NULL;

	mutex = kzalloc(sizeof(*mutex), GFP_KERNEL);
	if (!mutex)
		return NULL;

	mutex->cpp = cpp;
	mutex->target = target;
	mutex->address = address;
	mutex->key = key;
	mutex->depth = 0;

	return mutex;
}