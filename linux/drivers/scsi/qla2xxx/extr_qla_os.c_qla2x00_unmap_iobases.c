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
struct qla_hw_data {int /*<<< orphan*/ * msixbase; int /*<<< orphan*/ * mqiobase; int /*<<< orphan*/ * cregbase; int /*<<< orphan*/ * iobase; scalar_t__ nxdb_wr_ptr; scalar_t__ nx_pcibase; } ;
typedef  int /*<<< orphan*/  device_reg_t ;

/* Variables and functions */
 scalar_t__ IS_QLA27XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA28XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA83XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql2xdbwr ; 

__attribute__((used)) static void
qla2x00_unmap_iobases(struct qla_hw_data *ha)
{
	if (IS_QLA82XX(ha)) {

		iounmap((device_reg_t *)ha->nx_pcibase);
		if (!ql2xdbwr)
			iounmap((device_reg_t *)ha->nxdb_wr_ptr);
	} else {
		if (ha->iobase)
			iounmap(ha->iobase);

		if (ha->cregbase)
			iounmap(ha->cregbase);

		if (ha->mqiobase)
			iounmap(ha->mqiobase);

		if ((IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) &&
		    ha->msixbase)
			iounmap(ha->msixbase);
	}
}