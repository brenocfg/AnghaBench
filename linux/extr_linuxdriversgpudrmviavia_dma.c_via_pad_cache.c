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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  drm_via_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  HC_HEADER2 ; 
 int HC_ParaType_NotTex ; 
 int /*<<< orphan*/  VIA_OUT_RING_QW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  via_align_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  via_cmdbuf_wait (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * via_get_dma (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void via_pad_cache(drm_via_private_t *dev_priv, int qwords)
{
	uint32_t *vb;

	via_cmdbuf_wait(dev_priv, qwords + 2);
	vb = via_get_dma(dev_priv);
	VIA_OUT_RING_QW(HC_HEADER2, HC_ParaType_NotTex << 16);
	via_align_buffer(dev_priv, vb, qwords);
}