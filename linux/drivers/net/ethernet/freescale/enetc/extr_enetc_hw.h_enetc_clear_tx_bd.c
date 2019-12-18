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
typedef  union enetc_tx_bd {int dummy; } enetc_tx_bd ;

/* Variables and functions */
 int /*<<< orphan*/  memset (union enetc_tx_bd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void enetc_clear_tx_bd(union enetc_tx_bd *txbd)
{
	memset(txbd, 0, sizeof(*txbd));
}