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
struct hdmi_wp_data {scalar_t__ phys_base; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 scalar_t__ HDMI_WP_AUDIO_DATA ; 

phys_addr_t hdmi_wp_get_audio_dma_addr(struct hdmi_wp_data *wp)
{
	return wp->phys_base + HDMI_WP_AUDIO_DATA;
}