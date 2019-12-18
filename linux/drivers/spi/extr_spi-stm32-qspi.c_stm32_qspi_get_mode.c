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
struct stm32_qspi {int dummy; } ;

/* Variables and functions */
 int CCR_BUSWIDTH_4 ; 

__attribute__((used)) static int stm32_qspi_get_mode(struct stm32_qspi *qspi, u8 buswidth)
{
	if (buswidth == 4)
		return CCR_BUSWIDTH_4;

	return buswidth;
}