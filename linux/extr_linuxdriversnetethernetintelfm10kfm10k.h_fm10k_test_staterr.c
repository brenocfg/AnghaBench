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
struct TYPE_2__ {int staterr; } ;
union fm10k_rx_desc {TYPE_1__ d; } ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int __le32 ;

/* Variables and functions */
 int cpu_to_le32 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline __le32 fm10k_test_staterr(union fm10k_rx_desc *rx_desc,
					const u32 stat_err_bits)
{
	return rx_desc->d.staterr & cpu_to_le32(stat_err_bits);
}