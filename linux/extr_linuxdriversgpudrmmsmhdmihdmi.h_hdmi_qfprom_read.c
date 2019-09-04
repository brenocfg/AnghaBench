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
struct hdmi {scalar_t__ qfprom_mmio; } ;

/* Variables and functions */
 scalar_t__ msm_readl (scalar_t__) ; 

__attribute__((used)) static inline u32 hdmi_qfprom_read(struct hdmi *hdmi, u32 reg)
{
	return msm_readl(hdmi->qfprom_mmio + reg);
}