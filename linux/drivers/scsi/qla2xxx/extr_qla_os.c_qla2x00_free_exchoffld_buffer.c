#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {scalar_t__ exchoffld_size; int /*<<< orphan*/ * exchoffld_buf; int /*<<< orphan*/  exchoffld_buf_dma; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
qla2x00_free_exchoffld_buffer(struct qla_hw_data *ha)
{
	if (ha->exchoffld_buf) {
		dma_free_coherent(&ha->pdev->dev, ha->exchoffld_size,
		    ha->exchoffld_buf, ha->exchoffld_buf_dma);
		ha->exchoffld_buf = NULL;
		ha->exchoffld_size = 0;
	}
}