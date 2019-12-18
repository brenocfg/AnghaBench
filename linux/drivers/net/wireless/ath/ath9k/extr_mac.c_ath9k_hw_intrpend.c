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
typedef  int u32 ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_INTR_ASYNC_CAUSE ; 
 int AR_INTR_ASYNC_MASK_MCI ; 
 int AR_INTR_MAC_IRQ ; 
 int AR_INTR_SPURIOUS ; 
 int /*<<< orphan*/  AR_INTR_SYNC_CAUSE ; 
 int AR_INTR_SYNC_DEFAULT ; 
 scalar_t__ AR_SREV_9100 (struct ath_hw*) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 

bool ath9k_hw_intrpend(struct ath_hw *ah)
{
	u32 host_isr;

	if (AR_SREV_9100(ah))
		return true;

	host_isr = REG_READ(ah, AR_INTR_ASYNC_CAUSE);

	if (((host_isr & AR_INTR_MAC_IRQ) ||
	     (host_isr & AR_INTR_ASYNC_MASK_MCI)) &&
	    (host_isr != AR_INTR_SPURIOUS))
		return true;

	host_isr = REG_READ(ah, AR_INTR_SYNC_CAUSE);
	if ((host_isr & AR_INTR_SYNC_DEFAULT)
	    && (host_isr != AR_INTR_SPURIOUS))
		return true;

	return false;
}