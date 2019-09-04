#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_3__ {scalar_t__ type; size_t data1; size_t data2; } ;
typedef  TYPE_1__ pmi_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PMI_TYPE_FREQ_CHANGE ; 
 size_t* pmi_slow_mode_limit ; 
 int /*<<< orphan*/  pr_debug (char*,size_t,size_t) ; 

__attribute__((used)) static void cbe_cpufreq_handle_pmi(pmi_message_t pmi_msg)
{
	u8 node, slow_mode;

	BUG_ON(pmi_msg.type != PMI_TYPE_FREQ_CHANGE);

	node = pmi_msg.data1;
	slow_mode = pmi_msg.data2;

	pmi_slow_mode_limit[node] = slow_mode;

	pr_debug("cbe_handle_pmi: node: %d max_freq: %d\n", node, slow_mode);
}