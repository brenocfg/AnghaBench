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
struct ftmac100_rxdes {int rxdes0; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTMAC100_RXDES0_FTL ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ftmac100_rxdes_frame_too_long(struct ftmac100_rxdes *rxdes)
{
	return rxdes->rxdes0 & cpu_to_le32(FTMAC100_RXDES0_FTL);
}