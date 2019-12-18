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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hdmi_context {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ hdmi_map_reg (struct hdmi_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void hdmi_reg_writeb(struct hdmi_context *hdata,
				 u32 reg_id, u8 value)
{
	writel(value, hdata->regs + hdmi_map_reg(hdata, reg_id));
}