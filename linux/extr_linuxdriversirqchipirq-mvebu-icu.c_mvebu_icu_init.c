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
struct mvebu_icu {scalar_t__ base; int /*<<< orphan*/  initialized; } ;
struct msi_msg {int /*<<< orphan*/  address_lo; int /*<<< orphan*/  address_hi; } ;

/* Variables and functions */
 scalar_t__ ICU_CLRSPI_NSR_AH ; 
 scalar_t__ ICU_CLRSPI_NSR_AL ; 
 scalar_t__ ICU_SETSPI_NSR_AH ; 
 scalar_t__ ICU_SETSPI_NSR_AL ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mvebu_icu_init(struct mvebu_icu *icu, struct msi_msg *msg)
{
	if (atomic_cmpxchg(&icu->initialized, false, true))
		return;

	/* Set Clear/Set ICU SPI message address in AP */
	writel_relaxed(msg[0].address_hi, icu->base + ICU_SETSPI_NSR_AH);
	writel_relaxed(msg[0].address_lo, icu->base + ICU_SETSPI_NSR_AL);
	writel_relaxed(msg[1].address_hi, icu->base + ICU_CLRSPI_NSR_AH);
	writel_relaxed(msg[1].address_lo, icu->base + ICU_CLRSPI_NSR_AL);
}