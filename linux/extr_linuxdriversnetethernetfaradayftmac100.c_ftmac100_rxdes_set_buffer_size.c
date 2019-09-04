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
struct ftmac100_rxdes {int /*<<< orphan*/  rxdes1; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTMAC100_RXDES1_EDORR ; 
 int /*<<< orphan*/  FTMAC100_RXDES1_RXBUF_SIZE (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftmac100_rxdes_set_buffer_size(struct ftmac100_rxdes *rxdes,
					   unsigned int size)
{
	rxdes->rxdes1 &= cpu_to_le32(FTMAC100_RXDES1_EDORR);
	rxdes->rxdes1 |= cpu_to_le32(FTMAC100_RXDES1_RXBUF_SIZE(size));
}