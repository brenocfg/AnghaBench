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
struct smi_settings {int pack_data; int read_setup_time; int read_hold_time; int read_pace_time; int read_strobe_time; int write_setup_time; int write_hold_time; int write_pace_time; int write_strobe_time; int dma_enable; int dma_passthrough_enable; int dma_read_thresh; int dma_write_thresh; int dma_panic_read_thresh; int dma_panic_write_thresh; int /*<<< orphan*/  data_width; } ;
struct bcm2835_smi_instance {struct smi_settings settings; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMI_WIDTH_16BIT ; 

__attribute__((used)) static void smi_get_default_settings(struct bcm2835_smi_instance *inst)
{
	struct smi_settings *settings = &inst->settings;

	settings->data_width = SMI_WIDTH_16BIT;
	settings->pack_data = true;

	settings->read_setup_time = 1;
	settings->read_hold_time = 1;
	settings->read_pace_time = 1;
	settings->read_strobe_time = 3;

	settings->write_setup_time = settings->read_setup_time;
	settings->write_hold_time = settings->read_hold_time;
	settings->write_pace_time = settings->read_pace_time;
	settings->write_strobe_time = settings->read_strobe_time;

	settings->dma_enable = true;
	settings->dma_passthrough_enable = false;
	settings->dma_read_thresh = 0x01;
	settings->dma_write_thresh = 0x3f;
	settings->dma_panic_read_thresh = 0x20;
	settings->dma_panic_write_thresh = 0x20;
}