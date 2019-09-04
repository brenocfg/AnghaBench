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
struct platform_device {int dummy; } ;
struct dw_dma_platform_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct dw_dma_platform_data *
dw_dma_parse_dt(struct platform_device *pdev)
{
	return NULL;
}