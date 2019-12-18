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
struct TYPE_2__ {int status_error0; } ;
union ice_32b_rx_flex_desc {TYPE_1__ wb; } ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int cpu_to_le16 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static bool
ice_test_staterr(union ice_32b_rx_flex_desc *rx_desc, const u16 stat_err_bits)
{
	return !!(rx_desc->wb.status_error0 &
		  cpu_to_le16(stat_err_bits));
}