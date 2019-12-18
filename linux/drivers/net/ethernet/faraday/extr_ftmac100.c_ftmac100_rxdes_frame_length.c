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
struct ftmac100_rxdes {int /*<<< orphan*/  rxdes0; } ;

/* Variables and functions */
 unsigned int FTMAC100_RXDES0_RFL ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ftmac100_rxdes_frame_length(struct ftmac100_rxdes *rxdes)
{
	return le32_to_cpu(rxdes->rxdes0) & FTMAC100_RXDES0_RFL;
}