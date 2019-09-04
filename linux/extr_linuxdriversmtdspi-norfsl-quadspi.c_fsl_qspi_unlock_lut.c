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
struct fsl_qspi {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ QUADSPI_LCKCR ; 
 int /*<<< orphan*/  QUADSPI_LCKER_UNLOCK ; 
 scalar_t__ QUADSPI_LUTKEY ; 
 int /*<<< orphan*/  QUADSPI_LUTKEY_VALUE ; 
 int /*<<< orphan*/  qspi_writel (struct fsl_qspi*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void fsl_qspi_unlock_lut(struct fsl_qspi *q)
{
	qspi_writel(q, QUADSPI_LUTKEY_VALUE, q->iobase + QUADSPI_LUTKEY);
	qspi_writel(q, QUADSPI_LCKER_UNLOCK, q->iobase + QUADSPI_LCKCR);
}