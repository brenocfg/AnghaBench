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
struct s5p_mfc_ctx {int /*<<< orphan*/  bank1; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  s5p_mfc_release_generic_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s5p_mfc_release_codec_buffers_v6(struct s5p_mfc_ctx *ctx)
{
	s5p_mfc_release_generic_buf(ctx->dev, &ctx->bank1);
}