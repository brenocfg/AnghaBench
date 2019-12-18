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
struct qlcnic_host_tx_ring {int num_desc; int /*<<< orphan*/ * desc_head; } ;
struct cmd_desc_type0 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void dump_tx_ring_desc(struct qlcnic_host_tx_ring *tx_ring)
{
	int i;

	for (i = 0; i < tx_ring->num_desc; i++) {
		pr_info("TX Desc: %d\n", i);
		print_hex_dump(KERN_INFO, "TX: ", DUMP_PREFIX_OFFSET, 16, 1,
			       &tx_ring->desc_head[i],
			       sizeof(struct cmd_desc_type0), true);
	}
}