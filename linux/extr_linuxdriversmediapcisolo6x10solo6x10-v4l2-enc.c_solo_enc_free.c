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
struct solo_p2m_desc {int dummy; } ;
struct solo_enc_dev {int desc_nelts; int /*<<< orphan*/  hdl; int /*<<< orphan*/  vfd; int /*<<< orphan*/  desc_dma; int /*<<< orphan*/  desc_items; TYPE_1__* solo_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct solo_enc_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void solo_enc_free(struct solo_enc_dev *solo_enc)
{
	if (solo_enc == NULL)
		return;

	pci_free_consistent(solo_enc->solo_dev->pdev,
			sizeof(struct solo_p2m_desc) * solo_enc->desc_nelts,
			solo_enc->desc_items, solo_enc->desc_dma);
	video_unregister_device(solo_enc->vfd);
	v4l2_ctrl_handler_free(&solo_enc->hdl);
	kfree(solo_enc);
}