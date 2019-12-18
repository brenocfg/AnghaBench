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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct brcms_c_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_compute_cck_plcp (struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcms_c_compute_mimo_plcp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcms_c_compute_ofdm_plcp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_mcs_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ofdm_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brcms_c_compute_plcp(struct brcms_c_info *wlc, u32 rspec,
		     uint length, u8 *plcp)
{
	if (is_mcs_rate(rspec))
		brcms_c_compute_mimo_plcp(rspec, length, plcp);
	else if (is_ofdm_rate(rspec))
		brcms_c_compute_ofdm_plcp(rspec, length, plcp);
	else
		brcms_c_compute_cck_plcp(wlc, rspec, length, plcp);
}