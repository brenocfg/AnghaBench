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
typedef  int /*<<< orphan*/  uint32_t ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/  const) ; 
 scalar_t__ irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_stdout ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*) ; 
 int /*<<< orphan*/  stdout_bc ; 
 scalar_t__ stdout_irq ; 

__attribute__((used)) static int find_console_handle(void)
{
	struct device_node *np = of_stdout;
	const uint32_t *iprop;

	/* We don't care what the aliased node is actually called.  We only
	 * care if it's compatible with "epapr,hv-byte-channel", because that
	 * indicates that it's a byte channel node.
	 */
	if (!np || !of_device_is_compatible(np, "epapr,hv-byte-channel"))
		return 0;

	stdout_irq = irq_of_parse_and_map(np, 0);
	if (stdout_irq == NO_IRQ) {
		pr_err("ehv-bc: no 'interrupts' property in %pOF node\n", np);
		return 0;
	}

	/*
	 * The 'hv-handle' property contains the handle for this byte channel.
	 */
	iprop = of_get_property(np, "hv-handle", NULL);
	if (!iprop) {
		pr_err("ehv-bc: no 'hv-handle' property in %pOFn node\n",
		       np);
		return 0;
	}
	stdout_bc = be32_to_cpu(*iprop);
	return 1;
}