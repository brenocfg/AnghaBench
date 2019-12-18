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
struct platform_device_info {char* name; int id; int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  size_data; int /*<<< orphan*/ * data; int /*<<< orphan*/  num_res; int /*<<< orphan*/ * res; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_register_full (struct platform_device_info*) ; 

__attribute__((used)) static void adreno_device_register_headless(void)
{
	/* on imx5, we don't have a top-level mdp/dpu node
	 * this creates a dummy node for the driver for that case
	 */
	struct platform_device_info dummy_info = {
		.parent = NULL,
		.name = "msm",
		.id = -1,
		.res = NULL,
		.num_res = 0,
		.data = NULL,
		.size_data = 0,
		.dma_mask = ~0,
	};
	platform_device_register_full(&dummy_info);
}