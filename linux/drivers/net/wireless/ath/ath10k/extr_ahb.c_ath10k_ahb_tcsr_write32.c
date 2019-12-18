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
typedef  scalar_t__ u32 ;
struct ath10k_ahb {scalar_t__ tcsr_mem; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct ath10k_ahb* ath10k_ahb_priv (struct ath10k*) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ath10k_ahb_tcsr_write32(struct ath10k *ar, u32 offset, u32 value)
{
	struct ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	iowrite32(value, ar_ahb->tcsr_mem + offset);
}