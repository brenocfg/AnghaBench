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
struct fsl_qspi {TYPE_1__* devtype_data; } ;
struct TYPE_2__ {int driver_data; } ;

/* Variables and functions */
 int QUADSPI_QUIRK_TKT253890 ; 

__attribute__((used)) static inline int needs_fill_txfifo(struct fsl_qspi *q)
{
	return q->devtype_data->driver_data & QUADSPI_QUIRK_TKT253890;
}