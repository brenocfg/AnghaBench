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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_ce {TYPE_1__* bus_ops; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read32 ) (struct ath10k*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int /*<<< orphan*/  stub1 (struct ath10k*,int /*<<< orphan*/ ) ; 

inline u32 ath10k_pci_read32(struct ath10k *ar, u32 offset)
{
	struct ath10k_ce *ce = ath10k_ce_priv(ar);

	return ce->bus_ops->read32(ar, offset);
}