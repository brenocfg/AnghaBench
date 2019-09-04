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
struct nfp_cpp_area {int dummy; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 struct nfp_cpp_area* nfp_cpp_area_alloc_with_name (struct nfp_cpp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long,unsigned long) ; 

struct nfp_cpp_area *
nfp_cpp_area_alloc(struct nfp_cpp *cpp, u32 dest,
		   unsigned long long address, unsigned long size)
{
	return nfp_cpp_area_alloc_with_name(cpp, dest, NULL, address, size);
}