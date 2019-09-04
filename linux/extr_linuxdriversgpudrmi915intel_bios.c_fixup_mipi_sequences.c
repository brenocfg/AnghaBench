#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_5__ {int seq_version; size_t** sequence; size_t* deassert_seq; TYPE_1__* config; } ;
struct TYPE_6__ {TYPE_2__ dsi; } ;
struct drm_i915_private {TYPE_3__ vbt; } ;
struct TYPE_4__ {scalar_t__ is_cmd_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_i915_private*) ; 
 size_t MIPI_SEQ_ASSERT_RESET ; 
 size_t MIPI_SEQ_DEASSERT_RESET ; 
 size_t MIPI_SEQ_ELEM_END ; 
 size_t MIPI_SEQ_INIT_OTP ; 
 int get_init_otp_deassert_fragment_len (struct drm_i915_private*) ; 
 size_t* kmemdup (size_t*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fixup_mipi_sequences(struct drm_i915_private *dev_priv)
{
	u8 *init_otp;
	int len;

	/* Limit this to VLV for now. */
	if (!IS_VALLEYVIEW(dev_priv))
		return;

	/* Limit this to v1 vid-mode sequences */
	if (dev_priv->vbt.dsi.config->is_cmd_mode ||
	    dev_priv->vbt.dsi.seq_version != 1)
		return;

	/* Only do this if there are otp and assert seqs and no deassert seq */
	if (!dev_priv->vbt.dsi.sequence[MIPI_SEQ_INIT_OTP] ||
	    !dev_priv->vbt.dsi.sequence[MIPI_SEQ_ASSERT_RESET] ||
	    dev_priv->vbt.dsi.sequence[MIPI_SEQ_DEASSERT_RESET])
		return;

	/* The deassert-sequence ends at the first DSI packet */
	len = get_init_otp_deassert_fragment_len(dev_priv);
	if (!len)
		return;

	DRM_DEBUG_KMS("Using init OTP fragment to deassert reset\n");

	/* Copy the fragment, update seq byte and terminate it */
	init_otp = (u8 *)dev_priv->vbt.dsi.sequence[MIPI_SEQ_INIT_OTP];
	dev_priv->vbt.dsi.deassert_seq = kmemdup(init_otp, len + 1, GFP_KERNEL);
	if (!dev_priv->vbt.dsi.deassert_seq)
		return;
	dev_priv->vbt.dsi.deassert_seq[0] = MIPI_SEQ_DEASSERT_RESET;
	dev_priv->vbt.dsi.deassert_seq[len] = MIPI_SEQ_ELEM_END;
	/* Use the copy for deassert */
	dev_priv->vbt.dsi.sequence[MIPI_SEQ_DEASSERT_RESET] =
		dev_priv->vbt.dsi.deassert_seq;
	/* Replace the last byte of the fragment with init OTP seq byte */
	init_otp[len - 1] = MIPI_SEQ_INIT_OTP;
	/* And make MIPI_MIPI_SEQ_INIT_OTP point to it */
	dev_priv->vbt.dsi.sequence[MIPI_SEQ_INIT_OTP] = init_otp + len - 1;
}