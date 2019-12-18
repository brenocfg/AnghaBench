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
typedef  size_t u32 ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  (* base_add_sg_single ) (void*,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sge_size; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t MPI2_SGE_FLAGS_END_OF_BUFFER ; 
 size_t MPI2_SGE_FLAGS_END_OF_LIST ; 
 size_t MPI2_SGE_FLAGS_HOST_TO_IOC ; 
 size_t MPI2_SGE_FLAGS_LAST_ELEMENT ; 
 size_t MPI2_SGE_FLAGS_SHIFT ; 
 size_t MPI2_SGE_FLAGS_SIMPLE_ELEMENT ; 
 int /*<<< orphan*/  _base_build_zero_len_sge (struct MPT3SAS_ADAPTER*,void*) ; 
 int /*<<< orphan*/  stub1 (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_base_build_sg(struct MPT3SAS_ADAPTER *ioc, void *psge,
	dma_addr_t data_out_dma, size_t data_out_sz, dma_addr_t data_in_dma,
	size_t data_in_sz)
{
	u32 sgl_flags;

	if (!data_out_sz && !data_in_sz) {
		_base_build_zero_len_sge(ioc, psge);
		return;
	}

	if (data_out_sz && data_in_sz) {
		/* WRITE sgel first */
		sgl_flags = (MPI2_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI2_SGE_FLAGS_END_OF_BUFFER | MPI2_SGE_FLAGS_HOST_TO_IOC);
		sgl_flags = sgl_flags << MPI2_SGE_FLAGS_SHIFT;
		ioc->base_add_sg_single(psge, sgl_flags |
		    data_out_sz, data_out_dma);

		/* incr sgel */
		psge += ioc->sge_size;

		/* READ sgel last */
		sgl_flags = (MPI2_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI2_SGE_FLAGS_LAST_ELEMENT | MPI2_SGE_FLAGS_END_OF_BUFFER |
		    MPI2_SGE_FLAGS_END_OF_LIST);
		sgl_flags = sgl_flags << MPI2_SGE_FLAGS_SHIFT;
		ioc->base_add_sg_single(psge, sgl_flags |
		    data_in_sz, data_in_dma);
	} else if (data_out_sz) /* WRITE */ {
		sgl_flags = (MPI2_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI2_SGE_FLAGS_LAST_ELEMENT | MPI2_SGE_FLAGS_END_OF_BUFFER |
		    MPI2_SGE_FLAGS_END_OF_LIST | MPI2_SGE_FLAGS_HOST_TO_IOC);
		sgl_flags = sgl_flags << MPI2_SGE_FLAGS_SHIFT;
		ioc->base_add_sg_single(psge, sgl_flags |
		    data_out_sz, data_out_dma);
	} else if (data_in_sz) /* READ */ {
		sgl_flags = (MPI2_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI2_SGE_FLAGS_LAST_ELEMENT | MPI2_SGE_FLAGS_END_OF_BUFFER |
		    MPI2_SGE_FLAGS_END_OF_LIST);
		sgl_flags = sgl_flags << MPI2_SGE_FLAGS_SHIFT;
		ioc->base_add_sg_single(psge, sgl_flags |
		    data_in_sz, data_in_dma);
	}
}