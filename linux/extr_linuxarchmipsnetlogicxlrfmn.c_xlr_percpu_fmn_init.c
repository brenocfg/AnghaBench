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
typedef  int /*<<< orphan*/  uint32_t ;
struct xlr_fmn_info {int /*<<< orphan*/  credit_config; } ;
struct TYPE_2__ {int* bucket_size; struct xlr_fmn_info* cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  COP2_CC_INIT_CPU_DEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_FMN ; 
 int /*<<< orphan*/  nlm_cop2_disable_irqrestore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_cop2_enable_irqsave () ; 
 int nlm_core_id () ; 
 int /*<<< orphan*/  nlm_fmn_setup_intr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ nlm_thread_id () ; 
 int nlm_threads_per_core ; 
 int /*<<< orphan*/  nlm_write_c2_bucksize (int,int) ; 
 TYPE_1__ xlr_board_fmn_config ; 

void xlr_percpu_fmn_init(void)
{
	struct xlr_fmn_info *cpu_fmn_info;
	int *bucket_sizes;
	uint32_t flags;
	int id;

	BUG_ON(nlm_thread_id() != 0);
	id = nlm_core_id();

	bucket_sizes = xlr_board_fmn_config.bucket_size;
	cpu_fmn_info = &xlr_board_fmn_config.cpu[id];
	flags = nlm_cop2_enable_irqsave();

	/* Setup bucket sizes for the core. */
	nlm_write_c2_bucksize(0, bucket_sizes[id * 8 + 0]);
	nlm_write_c2_bucksize(1, bucket_sizes[id * 8 + 1]);
	nlm_write_c2_bucksize(2, bucket_sizes[id * 8 + 2]);
	nlm_write_c2_bucksize(3, bucket_sizes[id * 8 + 3]);
	nlm_write_c2_bucksize(4, bucket_sizes[id * 8 + 4]);
	nlm_write_c2_bucksize(5, bucket_sizes[id * 8 + 5]);
	nlm_write_c2_bucksize(6, bucket_sizes[id * 8 + 6]);
	nlm_write_c2_bucksize(7, bucket_sizes[id * 8 + 7]);

	/*
	 * For sending FMN messages, we need credits on the destination
	 * bucket. Program the credits this core has on the 128 possible
	 * destination buckets.
	 * We cannot use a loop here, because the the first argument has
	 * to be a constant integer value.
	 */
	COP2_CC_INIT_CPU_DEST(0, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(1, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(2, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(3, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(4, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(5, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(6, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(7, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(8, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(9, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(10, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(11, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(12, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(13, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(14, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(15, cpu_fmn_info->credit_config);

	/* enable FMN interrupts on this CPU */
	nlm_fmn_setup_intr(IRQ_FMN, (1 << nlm_threads_per_core) - 1);
	nlm_cop2_disable_irqrestore(flags);
}