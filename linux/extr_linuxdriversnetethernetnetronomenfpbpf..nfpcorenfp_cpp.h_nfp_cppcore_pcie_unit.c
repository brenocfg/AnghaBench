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
typedef  int /*<<< orphan*/  u8 ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_CPP_INTERFACE_UNIT_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_cpp_interface (struct nfp_cpp*) ; 

__attribute__((used)) static inline u8 nfp_cppcore_pcie_unit(struct nfp_cpp *cpp)
{
	return NFP_CPP_INTERFACE_UNIT_of(nfp_cpp_interface(cpp));
}