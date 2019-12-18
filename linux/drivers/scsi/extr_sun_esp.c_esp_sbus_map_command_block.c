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
struct esp {int /*<<< orphan*/  command_block; int /*<<< orphan*/  command_block_dma; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp_sbus_map_command_block(struct esp *esp)
{
	esp->command_block = dma_alloc_coherent(esp->dev, 16,
						&esp->command_block_dma,
						GFP_KERNEL);
	if (!esp->command_block)
		return -ENOMEM;
	return 0;
}