#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int status_error_len; } ;
struct TYPE_4__ {TYPE_1__ qword1; } ;
union iavf_rx_desc {TYPE_2__ wb; } ;
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int cpu_to_le64 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline bool iavf_test_staterr(union iavf_rx_desc *rx_desc,
				     const u64 stat_err_bits)
{
	return !!(rx_desc->wb.qword1.status_error_len &
		  cpu_to_le64(stat_err_bits));
}