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
typedef  int u8 ;
struct MPT3SAS_ADAPTER {int dummy; } ;

/* Variables and functions */
 int MPI25_IEEE_SGE_FLAGS_END_OF_LIST ; 
 int MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT ; 
 int MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR ; 
 int /*<<< orphan*/  _base_add_sg_single_ieee (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
_base_build_zero_len_sge_ieee(struct MPT3SAS_ADAPTER *ioc, void *paddr)
{
	u8 sgl_flags = (MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT |
		MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR |
		MPI25_IEEE_SGE_FLAGS_END_OF_LIST);

	_base_add_sg_single_ieee(paddr, sgl_flags, 0, 0, -1);
}