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
struct mvebu_icu_subset_data {scalar_t__ icu_group; scalar_t__ offset_clr_al; scalar_t__ offset_clr_ah; scalar_t__ offset_set_al; scalar_t__ offset_set_ah; } ;
struct mvebu_icu_msi_data {int /*<<< orphan*/  initialized; struct mvebu_icu_subset_data* subset_data; } ;
struct mvebu_icu {scalar_t__ base; } ;
struct msi_msg {int /*<<< orphan*/  address_lo; int /*<<< orphan*/  address_hi; } ;

/* Variables and functions */
 scalar_t__ ICU_GRP_NSR ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mvebu_icu_init(struct mvebu_icu *icu,
			   struct mvebu_icu_msi_data *msi_data,
			   struct msi_msg *msg)
{
	const struct mvebu_icu_subset_data *subset = msi_data->subset_data;

	if (atomic_cmpxchg(&msi_data->initialized, false, true))
		return;

	/* Set 'SET' ICU SPI message address in AP */
	writel_relaxed(msg[0].address_hi, icu->base + subset->offset_set_ah);
	writel_relaxed(msg[0].address_lo, icu->base + subset->offset_set_al);

	if (subset->icu_group != ICU_GRP_NSR)
		return;

	/* Set 'CLEAR' ICU SPI message address in AP (level-MSI only) */
	writel_relaxed(msg[1].address_hi, icu->base + subset->offset_clr_ah);
	writel_relaxed(msg[1].address_lo, icu->base + subset->offset_clr_al);
}