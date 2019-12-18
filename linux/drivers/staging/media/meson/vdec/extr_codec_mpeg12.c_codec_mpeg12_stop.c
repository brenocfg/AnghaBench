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
struct codec_mpeg12 {int /*<<< orphan*/  workspace_paddr; scalar_t__ workspace_vaddr; } ;
struct amvdec_session {struct amvdec_core* core; struct codec_mpeg12* priv; } ;
struct amvdec_core {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_WORKSPACE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int codec_mpeg12_stop(struct amvdec_session *sess)
{
	struct codec_mpeg12 *mpeg12 = sess->priv;
	struct amvdec_core *core = sess->core;

	if (mpeg12->workspace_vaddr)
		dma_free_coherent(core->dev, SIZE_WORKSPACE,
				  mpeg12->workspace_vaddr,
				  mpeg12->workspace_paddr);

	return 0;
}