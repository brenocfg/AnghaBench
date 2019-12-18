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
struct ath_hw {int /*<<< orphan*/  opmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_hw_set_operating_mode (struct ath_hw*,int /*<<< orphan*/ ) ; 

void ath9k_hw_setopmode(struct ath_hw *ah)
{
	ath9k_hw_set_operating_mode(ah, ah->opmode);
}