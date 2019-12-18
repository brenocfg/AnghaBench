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
struct switchtec_ntb {int nr_direct_mw; int nr_rsvd_luts; } ;

/* Variables and functions */

__attribute__((used)) static int lut_index(struct switchtec_ntb *sndev, int mw_idx)
{
	return mw_idx - sndev->nr_direct_mw + sndev->nr_rsvd_luts;
}