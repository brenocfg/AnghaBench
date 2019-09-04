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
struct pcpu {int /*<<< orphan*/  ec_clk; int /*<<< orphan*/  ec_mask; } ;

/* Variables and functions */
 int SIGP_EMERGENCY_SIGNAL ; 
 int SIGP_EXTERNAL_CALL ; 
 int /*<<< orphan*/  get_tod_clock_fast () ; 
 scalar_t__ pcpu_running (struct pcpu*) ; 
 int /*<<< orphan*/  pcpu_sigp_retry (struct pcpu*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcpu_ec_call(struct pcpu *pcpu, int ec_bit)
{
	int order;

	if (test_and_set_bit(ec_bit, &pcpu->ec_mask))
		return;
	order = pcpu_running(pcpu) ? SIGP_EXTERNAL_CALL : SIGP_EMERGENCY_SIGNAL;
	pcpu->ec_clk = get_tod_clock_fast();
	pcpu_sigp_retry(pcpu, order, 0);
}