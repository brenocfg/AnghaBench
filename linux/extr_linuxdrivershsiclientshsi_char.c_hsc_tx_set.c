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
struct hsi_config {scalar_t__ mode; int num_hw_channels; scalar_t__ arb_mode; int /*<<< orphan*/  speed; } ;
struct hsi_client {struct hsi_config tx_cfg; } ;
struct hsc_tx_config {scalar_t__ mode; int channels; scalar_t__ arb_mode; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int EINVAL ; 
 int HSC_DEVS ; 
 scalar_t__ HSI_ARB_PRIO ; 
 scalar_t__ HSI_ARB_RR ; 
 scalar_t__ HSI_MODE_FRAME ; 
 scalar_t__ HSI_MODE_STREAM ; 
 int hsi_setup (struct hsi_client*) ; 

__attribute__((used)) static int hsc_tx_set(struct hsi_client *cl, struct hsc_tx_config *txc)
{
	struct hsi_config tmp;
	int ret;

	if ((txc->mode != HSI_MODE_STREAM) && (txc->mode != HSI_MODE_FRAME))
		return -EINVAL;
	if ((txc->channels == 0) || (txc->channels > HSC_DEVS))
		return -EINVAL;
	if (txc->channels & (txc->channels - 1))
		return -EINVAL;
	if ((txc->arb_mode != HSI_ARB_RR) && (txc->arb_mode != HSI_ARB_PRIO))
		return -EINVAL;
	tmp = cl->tx_cfg;
	cl->tx_cfg.mode = txc->mode;
	cl->tx_cfg.num_hw_channels = txc->channels;
	cl->tx_cfg.speed = txc->speed;
	cl->tx_cfg.arb_mode = txc->arb_mode;
	ret = hsi_setup(cl);
	if (ret < 0) {
		cl->tx_cfg = tmp;
		return ret;
	}

	return ret;
}