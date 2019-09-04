#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qib_ctxtdata {TYPE_2__* dd; } ;
struct qib_base_info {int spi_runtime_flags; } ;
struct TYPE_4__ {int flags; TYPE_1__* cspec; } ;
struct TYPE_3__ {scalar_t__ r1; } ;

/* Variables and functions */
 int QIB_RUNTIME_CTXT_MSB_IN_QP ; 
 int QIB_RUNTIME_HDRSUPP ; 
 int QIB_RUNTIME_NODMA_RTAIL ; 
 int QIB_RUNTIME_PCIE ; 
 int QIB_RUNTIME_RCHK ; 
 int QIB_RUNTIME_SDMA ; 
 int QIB_RUNTIME_SPECIAL_TRIGGER ; 
 int QIB_USE_SPCL_TRIG ; 

__attribute__((used)) static int qib_7322_get_base_info(struct qib_ctxtdata *rcd,
				  struct qib_base_info *kinfo)
{
	kinfo->spi_runtime_flags |= QIB_RUNTIME_CTXT_MSB_IN_QP |
		QIB_RUNTIME_PCIE | QIB_RUNTIME_NODMA_RTAIL |
		QIB_RUNTIME_HDRSUPP | QIB_RUNTIME_SDMA;
	if (rcd->dd->cspec->r1)
		kinfo->spi_runtime_flags |= QIB_RUNTIME_RCHK;
	if (rcd->dd->flags & QIB_USE_SPCL_TRIG)
		kinfo->spi_runtime_flags |= QIB_RUNTIME_SPECIAL_TRIGGER;

	return 0;
}