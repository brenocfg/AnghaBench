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
struct TYPE_4__ {int /*<<< orphan*/ * dma; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dma; } ;
struct qup_i2c_dev {TYPE_2__ brx; TYPE_1__ btx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qup_i2c_rel_dma(struct qup_i2c_dev *qup)
{
	if (qup->btx.dma)
		dma_release_channel(qup->btx.dma);
	if (qup->brx.dma)
		dma_release_channel(qup->brx.dma);
	qup->btx.dma = NULL;
	qup->brx.dma = NULL;
}