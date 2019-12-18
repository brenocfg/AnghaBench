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
struct hdmi_context {int regs; } ;

/* Variables and functions */
 int hdmi_map_reg (struct hdmi_context*,int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static inline void hdmi_reg_writev(struct hdmi_context *hdata, u32 reg_id,
				   int bytes, u32 val)
{
	reg_id = hdmi_map_reg(hdata, reg_id);

	while (--bytes >= 0) {
		writel(val & 0xff, hdata->regs + reg_id);
		val >>= 8;
		reg_id += 4;
	}
}