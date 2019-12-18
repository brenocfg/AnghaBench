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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;

/* Variables and functions */
 int MCFQSPI_BUSCLK ; 
 int /*<<< orphan*/  clamp (int,unsigned int,unsigned int) ; 

__attribute__((used)) static u8 mcfqspi_qmr_baud(u32 speed_hz)
{
	return clamp((MCFQSPI_BUSCLK + speed_hz - 1) / speed_hz, 2u, 255u);
}