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
typedef  int u8 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ RCV_RSM_CFG ; 
 scalar_t__ RCV_RSM_MATCH ; 
 scalar_t__ RCV_RSM_SELECT ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_rsm_rule(struct hfi1_devdata *dd, u8 rule_index)
{
	write_csr(dd, RCV_RSM_CFG + (8 * rule_index), 0);
	write_csr(dd, RCV_RSM_SELECT + (8 * rule_index), 0);
	write_csr(dd, RCV_RSM_MATCH + (8 * rule_index), 0);
}