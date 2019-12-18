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
union htt_rx_pn_t {int pn48; } ;

/* Variables and functions */

__attribute__((used)) static bool ath10k_htt_rx_pn_cmp48(union htt_rx_pn_t *new_pn,
				   union htt_rx_pn_t *old_pn)
{
	return ((new_pn->pn48 & 0xffffffffffffULL) <=
		(old_pn->pn48 & 0xffffffffffffULL));
}