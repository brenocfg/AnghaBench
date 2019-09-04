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
struct ftmac100_txdes {scalar_t__ txdes3; scalar_t__ txdes2; int /*<<< orphan*/  txdes1; scalar_t__ txdes0; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTMAC100_TXDES1_EDOTR ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftmac100_txdes_reset(struct ftmac100_txdes *txdes)
{
	/* clear all except end of ring bit */
	txdes->txdes0 = 0;
	txdes->txdes1 &= cpu_to_le32(FTMAC100_TXDES1_EDOTR);
	txdes->txdes2 = 0;
	txdes->txdes3 = 0;
}