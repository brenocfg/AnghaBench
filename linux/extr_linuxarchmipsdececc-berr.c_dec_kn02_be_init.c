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

/* Variables and functions */
 scalar_t__ CKSEG1ADDR (scalar_t__) ; 
 scalar_t__ KN02_CHKSYN ; 
 scalar_t__ KN02_CSR ; 
 int volatile KN02_CSR_CORRECT ; 
 int volatile KN02_CSR_DIAGCHK ; 
 int volatile KN02_CSR_DIAGGEN ; 
 int volatile KN02_CSR_LEDS ; 
 scalar_t__ KN02_ERRADDR ; 
 scalar_t__ KN02_SLOT_BASE ; 
 int volatile cached_kn02_csr ; 
 int /*<<< orphan*/  iob () ; 
 void* kn0x_chksyn ; 
 void* kn0x_erraddr ; 

__attribute__((used)) static inline void dec_kn02_be_init(void)
{
	volatile u32 *csr = (void *)CKSEG1ADDR(KN02_SLOT_BASE + KN02_CSR);

	kn0x_erraddr = (void *)CKSEG1ADDR(KN02_SLOT_BASE + KN02_ERRADDR);
	kn0x_chksyn = (void *)CKSEG1ADDR(KN02_SLOT_BASE + KN02_CHKSYN);

	/* Preset write-only bits of the Control Register cache. */
	cached_kn02_csr = *csr | KN02_CSR_LEDS;

	/* Set normal ECC detection and generation. */
	cached_kn02_csr &= ~(KN02_CSR_DIAGCHK | KN02_CSR_DIAGGEN);
	/* Enable ECC correction. */
	cached_kn02_csr |= KN02_CSR_CORRECT;
	*csr = cached_kn02_csr;
	iob();
}