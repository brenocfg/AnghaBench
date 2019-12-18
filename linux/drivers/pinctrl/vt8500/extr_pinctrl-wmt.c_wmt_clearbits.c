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
typedef  scalar_t__ u32 ;
struct wmt_pinctrl_data {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void wmt_clearbits(struct wmt_pinctrl_data *data, u32 reg,
				   u32 mask)
{
	u32 val;

	val = readl_relaxed(data->base + reg);
	val &= ~mask;
	writel_relaxed(val, data->base + reg);
}