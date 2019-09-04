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
struct ftmac100_txdes {int /*<<< orphan*/  txdes1; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTMAC100_TXDES1_TXIC ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftmac100_txdes_set_txint(struct ftmac100_txdes *txdes)
{
	txdes->txdes1 |= cpu_to_le32(FTMAC100_TXDES1_TXIC);
}