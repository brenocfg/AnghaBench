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
struct hdmi_pll_8996 {scalar_t__* mmio_qserdes_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_writel (int,scalar_t__) ; 

__attribute__((used)) static inline void hdmi_tx_chan_write(struct hdmi_pll_8996 *pll, int channel,
				      int offset, int data)
{
	 msm_writel(data, pll->mmio_qserdes_tx[channel] + offset);
}