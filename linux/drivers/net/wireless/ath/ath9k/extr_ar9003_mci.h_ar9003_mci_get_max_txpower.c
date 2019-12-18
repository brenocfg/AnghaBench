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
typedef  int u16 ;
struct ath_hw {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 ar9003_mci_get_max_txpower(struct ath_hw *ah, u8 ctlmode)
{
	return -1;
}