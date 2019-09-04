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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pcc_cpu {scalar_t__ input_offset; } ;
struct cpufreq_policy {int cpu; int /*<<< orphan*/  cur; } ;
struct cpufreq_freqs {unsigned int new; int /*<<< orphan*/  old; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  command; int /*<<< orphan*/  nominal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_SZ ; 
 int /*<<< orphan*/  CMD_COMPLETE ; 
 int /*<<< orphan*/  CMD_SET_FREQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpufreq_freq_transition_begin (struct cpufreq_policy*,struct cpufreq_freqs*) ; 
 int /*<<< orphan*/  cpufreq_freq_transition_end (struct cpufreq_policy*,struct cpufreq_freqs*,int) ; 
 int /*<<< orphan*/  ioread16 (int /*<<< orphan*/ *) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcc_cmd () ; 
 int /*<<< orphan*/  pcc_cpu_info ; 
 int /*<<< orphan*/  pcc_lock ; 
 TYPE_1__* pcch_hdr ; 
 scalar_t__ pcch_virt_addr ; 
 struct pcc_cpu* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcc_cpufreq_target(struct cpufreq_policy *policy,
			      unsigned int target_freq,
			      unsigned int relation)
{
	struct pcc_cpu *pcc_cpu_data;
	struct cpufreq_freqs freqs;
	u16 status;
	u32 input_buffer;
	int cpu;

	cpu = policy->cpu;
	pcc_cpu_data = per_cpu_ptr(pcc_cpu_info, cpu);

	pr_debug("target: CPU %d should go to target freq: %d "
		"(virtual) input_offset is 0x%p\n",
		cpu, target_freq,
		(pcch_virt_addr + pcc_cpu_data->input_offset));

	freqs.old = policy->cur;
	freqs.new = target_freq;
	cpufreq_freq_transition_begin(policy, &freqs);
	spin_lock(&pcc_lock);

	input_buffer = 0x1 | (((target_freq * 100)
			       / (ioread32(&pcch_hdr->nominal) * 1000)) << 8);
	iowrite32(input_buffer,
			(pcch_virt_addr + pcc_cpu_data->input_offset));
	iowrite16(CMD_SET_FREQ, &pcch_hdr->command);

	pcc_cmd();

	/* Clear the input buffer - we are done with the current command */
	memset_io((pcch_virt_addr + pcc_cpu_data->input_offset), 0, BUF_SZ);

	status = ioread16(&pcch_hdr->status);
	iowrite16(0, &pcch_hdr->status);

	cpufreq_freq_transition_end(policy, &freqs, status != CMD_COMPLETE);
	spin_unlock(&pcc_lock);

	if (status != CMD_COMPLETE) {
		pr_debug("target: FAILED for cpu %d, with status: 0x%x\n",
			cpu, status);
		return -EINVAL;
	}

	pr_debug("target: was SUCCESSFUL for cpu %d\n", cpu);

	return 0;
}