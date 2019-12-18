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
typedef  int uint32_t ;
struct xadc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XADC_ZYNQ_REG_DFIFO ; 
 int /*<<< orphan*/  XADC_ZYNQ_REG_STATUS ; 
 int XADC_ZYNQ_STATUS_DFIFOE ; 
 int /*<<< orphan*/  xadc_read_reg (struct xadc*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void xadc_zynq_drain_fifo(struct xadc *xadc)
{
	uint32_t status, tmp;

	xadc_read_reg(xadc, XADC_ZYNQ_REG_STATUS, &status);

	while (!(status & XADC_ZYNQ_STATUS_DFIFOE)) {
		xadc_read_reg(xadc, XADC_ZYNQ_REG_DFIFO, &tmp);
		xadc_read_reg(xadc, XADC_ZYNQ_REG_STATUS, &status);
	}
}