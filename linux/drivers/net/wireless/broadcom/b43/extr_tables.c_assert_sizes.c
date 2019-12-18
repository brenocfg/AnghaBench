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

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ B43_TAB_FINEFREQA_SIZE ; 
 scalar_t__ B43_TAB_FINEFREQG_SIZE ; 
 scalar_t__ B43_TAB_NOISEA2_SIZE ; 
 scalar_t__ B43_TAB_NOISEA3_SIZE ; 
 scalar_t__ B43_TAB_NOISEG1_SIZE ; 
 scalar_t__ B43_TAB_NOISEG2_SIZE ; 
 scalar_t__ B43_TAB_NOISESCALE_SIZE ; 
 scalar_t__ B43_TAB_RETARD_SIZE ; 
 scalar_t__ B43_TAB_ROTOR_SIZE ; 
 scalar_t__ B43_TAB_RSSIAGC1_SIZE ; 
 scalar_t__ B43_TAB_RSSIAGC2_SIZE ; 
 scalar_t__ B43_TAB_SIGMASQR_SIZE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  b43_tab_finefreqa ; 
 int /*<<< orphan*/  b43_tab_finefreqg ; 
 int /*<<< orphan*/  b43_tab_noisea2 ; 
 int /*<<< orphan*/  b43_tab_noisea3 ; 
 int /*<<< orphan*/  b43_tab_noiseg1 ; 
 int /*<<< orphan*/  b43_tab_noiseg2 ; 
 int /*<<< orphan*/  b43_tab_noisescalea2 ; 
 int /*<<< orphan*/  b43_tab_noisescalea3 ; 
 int /*<<< orphan*/  b43_tab_noisescaleg1 ; 
 int /*<<< orphan*/  b43_tab_noisescaleg2 ; 
 int /*<<< orphan*/  b43_tab_noisescaleg3 ; 
 int /*<<< orphan*/  b43_tab_retard ; 
 int /*<<< orphan*/  b43_tab_rotor ; 
 int /*<<< orphan*/  b43_tab_rssiagc1 ; 
 int /*<<< orphan*/  b43_tab_rssiagc2 ; 
 int /*<<< orphan*/  b43_tab_sigmasqr1 ; 
 int /*<<< orphan*/  b43_tab_sigmasqr2 ; 

__attribute__((used)) static inline void assert_sizes(void)
{
	BUILD_BUG_ON(B43_TAB_ROTOR_SIZE != ARRAY_SIZE(b43_tab_rotor));
	BUILD_BUG_ON(B43_TAB_RETARD_SIZE != ARRAY_SIZE(b43_tab_retard));
	BUILD_BUG_ON(B43_TAB_FINEFREQA_SIZE != ARRAY_SIZE(b43_tab_finefreqa));
	BUILD_BUG_ON(B43_TAB_FINEFREQG_SIZE != ARRAY_SIZE(b43_tab_finefreqg));
	BUILD_BUG_ON(B43_TAB_NOISEA2_SIZE != ARRAY_SIZE(b43_tab_noisea2));
	BUILD_BUG_ON(B43_TAB_NOISEA3_SIZE != ARRAY_SIZE(b43_tab_noisea3));
	BUILD_BUG_ON(B43_TAB_NOISEG1_SIZE != ARRAY_SIZE(b43_tab_noiseg1));
	BUILD_BUG_ON(B43_TAB_NOISEG2_SIZE != ARRAY_SIZE(b43_tab_noiseg2));
	BUILD_BUG_ON(B43_TAB_NOISESCALE_SIZE !=
		     ARRAY_SIZE(b43_tab_noisescalea2));
	BUILD_BUG_ON(B43_TAB_NOISESCALE_SIZE !=
		     ARRAY_SIZE(b43_tab_noisescalea3));
	BUILD_BUG_ON(B43_TAB_NOISESCALE_SIZE !=
		     ARRAY_SIZE(b43_tab_noisescaleg1));
	BUILD_BUG_ON(B43_TAB_NOISESCALE_SIZE !=
		     ARRAY_SIZE(b43_tab_noisescaleg2));
	BUILD_BUG_ON(B43_TAB_NOISESCALE_SIZE !=
		     ARRAY_SIZE(b43_tab_noisescaleg3));
	BUILD_BUG_ON(B43_TAB_SIGMASQR_SIZE != ARRAY_SIZE(b43_tab_sigmasqr1));
	BUILD_BUG_ON(B43_TAB_SIGMASQR_SIZE != ARRAY_SIZE(b43_tab_sigmasqr2));
	BUILD_BUG_ON(B43_TAB_RSSIAGC1_SIZE != ARRAY_SIZE(b43_tab_rssiagc1));
	BUILD_BUG_ON(B43_TAB_RSSIAGC2_SIZE != ARRAY_SIZE(b43_tab_rssiagc2));
}