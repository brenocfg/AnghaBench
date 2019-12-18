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
struct TYPE_2__ {void* base_gprlbc; void* base_gorlbc; void* base_gptlbc; void* base_gotlbc; void* base_mprc; void* base_gotc; void* base_gptc; void* base_gorc; void* base_gprc; void* last_gprlbc; void* last_gorlbc; void* last_gptlbc; void* last_gotlbc; void* last_mprc; void* last_gotc; void* last_gptc; void* last_gorc; void* last_gprc; } ;
struct e1000_hw {int dummy; } ;
struct igbvf_adapter {TYPE_1__ stats; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFGORC ; 
 int /*<<< orphan*/  VFGORLBC ; 
 int /*<<< orphan*/  VFGOTC ; 
 int /*<<< orphan*/  VFGOTLBC ; 
 int /*<<< orphan*/  VFGPRC ; 
 int /*<<< orphan*/  VFGPRLBC ; 
 int /*<<< orphan*/  VFGPTC ; 
 int /*<<< orphan*/  VFGPTLBC ; 
 int /*<<< orphan*/  VFMPRC ; 
 void* er32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igbvf_initialize_last_counter_stats(struct igbvf_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	adapter->stats.last_gprc = er32(VFGPRC);
	adapter->stats.last_gorc = er32(VFGORC);
	adapter->stats.last_gptc = er32(VFGPTC);
	adapter->stats.last_gotc = er32(VFGOTC);
	adapter->stats.last_mprc = er32(VFMPRC);
	adapter->stats.last_gotlbc = er32(VFGOTLBC);
	adapter->stats.last_gptlbc = er32(VFGPTLBC);
	adapter->stats.last_gorlbc = er32(VFGORLBC);
	adapter->stats.last_gprlbc = er32(VFGPRLBC);

	adapter->stats.base_gprc = er32(VFGPRC);
	adapter->stats.base_gorc = er32(VFGORC);
	adapter->stats.base_gptc = er32(VFGPTC);
	adapter->stats.base_gotc = er32(VFGOTC);
	adapter->stats.base_mprc = er32(VFMPRC);
	adapter->stats.base_gotlbc = er32(VFGOTLBC);
	adapter->stats.base_gptlbc = er32(VFGPTLBC);
	adapter->stats.base_gorlbc = er32(VFGORLBC);
	adapter->stats.base_gprlbc = er32(VFGPRLBC);
}