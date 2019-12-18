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
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DYNACK ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_ack_timeout (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_set_cts_timeout (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_setslottime (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void ath_dynack_set_timeout(struct ath_hw *ah, int to)
{
	struct ath_common *common = ath9k_hw_common(ah);
	int slottime = (to - 3) / 2;

	ath_dbg(common, DYNACK, "ACK timeout %u slottime %u\n",
		to, slottime);
	ath9k_hw_setslottime(ah, slottime);
	ath9k_hw_set_ack_timeout(ah, to);
	ath9k_hw_set_cts_timeout(ah, to);
}