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
struct seq_file {struct adapter* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;
typedef  int loff_t ;

/* Variables and functions */
 int NUM_MPS_CLS_SRAM_L_INSTANCES ; 
 int NUM_MPS_T5_CLS_SRAM_L_INSTANCES ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *mps_tcam_get_idx(struct seq_file *seq, loff_t pos)
{
	struct adapter *adap = seq->private;
	int max_mac_addr = is_t4(adap->params.chip) ?
				NUM_MPS_CLS_SRAM_L_INSTANCES :
				NUM_MPS_T5_CLS_SRAM_L_INSTANCES;
	return ((pos <= max_mac_addr) ? (void *)(uintptr_t)(pos + 1) : NULL);
}