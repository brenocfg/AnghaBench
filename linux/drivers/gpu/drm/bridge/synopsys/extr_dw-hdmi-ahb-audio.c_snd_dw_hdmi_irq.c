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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {scalar_t__ base; } ;
struct snd_dw_hdmi {int /*<<< orphan*/  lock; struct snd_pcm_substream* substream; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ HDMI_IH_AHBDMAAUD_STAT0 ; 
 unsigned int HDMI_IH_AHBDMAAUD_STAT0_DONE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dw_hdmi_start_dma (struct snd_dw_hdmi*) ; 
 unsigned int readb_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t snd_dw_hdmi_irq(int irq, void *data)
{
	struct snd_dw_hdmi *dw = data;
	struct snd_pcm_substream *substream;
	unsigned stat;

	stat = readb_relaxed(dw->data.base + HDMI_IH_AHBDMAAUD_STAT0);
	if (!stat)
		return IRQ_NONE;

	writeb_relaxed(stat, dw->data.base + HDMI_IH_AHBDMAAUD_STAT0);

	substream = dw->substream;
	if (stat & HDMI_IH_AHBDMAAUD_STAT0_DONE && substream) {
		snd_pcm_period_elapsed(substream);

		spin_lock(&dw->lock);
		if (dw->substream)
			dw_hdmi_start_dma(dw);
		spin_unlock(&dw->lock);
	}

	return IRQ_HANDLED;
}