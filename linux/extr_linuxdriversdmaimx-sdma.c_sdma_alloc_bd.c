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
typedef  int u32 ;
struct sdma_desc {int num_bd; int /*<<< orphan*/  bd; int /*<<< orphan*/  bd_phys; } ;
struct sdma_buffer_descriptor {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  dma_zalloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdma_alloc_bd(struct sdma_desc *desc)
{
	u32 bd_size = desc->num_bd * sizeof(struct sdma_buffer_descriptor);
	int ret = 0;

	desc->bd = dma_zalloc_coherent(NULL, bd_size, &desc->bd_phys,
					GFP_NOWAIT);
	if (!desc->bd) {
		ret = -ENOMEM;
		goto out;
	}
out:
	return ret;
}