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
typedef  scalar_t__ u64 ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_trans_write32 (struct iwl_trans*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_iowrite64 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

void iwl_write64(struct iwl_trans *trans, u64 ofs, u64 val)
{
	trace_iwlwifi_dev_iowrite64(trans->dev, ofs, val);
	iwl_trans_write32(trans, ofs, lower_32_bits(val));
	iwl_trans_write32(trans, ofs + 4, upper_32_bits(val));
}