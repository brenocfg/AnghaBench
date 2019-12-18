#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath_tx_info {int dummy; } ;
struct ath_hw {int dummy; } ;
struct TYPE_2__ {void (* set_txdesc ) (struct ath_hw*,void*,struct ath_tx_info*) ;} ;

/* Variables and functions */
 TYPE_1__* ath9k_hw_ops (struct ath_hw*) ; 
 void stub1 (struct ath_hw*,void*,struct ath_tx_info*) ; 

__attribute__((used)) static inline void ath9k_hw_set_txdesc(struct ath_hw *ah, void *ds,
				       struct ath_tx_info *i)
{
	return ath9k_hw_ops(ah)->set_txdesc(ah, ds, i);
}