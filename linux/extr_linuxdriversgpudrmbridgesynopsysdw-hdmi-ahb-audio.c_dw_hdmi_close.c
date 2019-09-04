#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_dw_hdmi* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; scalar_t__ base; } ;
struct snd_dw_hdmi {TYPE_1__ data; } ;

/* Variables and functions */
 scalar_t__ HDMI_IH_MUTE_AHBDMAAUD_STAT0 ; 
 int /*<<< orphan*/  HDMI_IH_MUTE_AHBDMAAUD_STAT0_ALL ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct snd_dw_hdmi*) ; 
 int /*<<< orphan*/  writeb_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dw_hdmi_close(struct snd_pcm_substream *substream)
{
	struct snd_dw_hdmi *dw = substream->private_data;

	/* Mute all interrupts */
	writeb_relaxed(HDMI_IH_MUTE_AHBDMAAUD_STAT0_ALL,
		       dw->data.base + HDMI_IH_MUTE_AHBDMAAUD_STAT0);

	free_irq(dw->data.irq, dw);

	return 0;
}