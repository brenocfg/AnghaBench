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
struct of_phandle_args {int dummy; } ;
struct of_dma {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct dma_chan *at_dma_xlate(struct of_phandle_args *dma_spec,
				     struct of_dma *of_dma)
{
	return NULL;
}