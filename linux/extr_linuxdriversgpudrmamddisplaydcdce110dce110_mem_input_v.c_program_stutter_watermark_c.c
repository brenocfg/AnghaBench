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
struct dce_watermarks {int dummy; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmDPGV1_PIPE_STUTTER_CONTROL ; 
 int /*<<< orphan*/  mmDPGV1_WATERMARK_MASK_CONTROL ; 
 int /*<<< orphan*/  program_stutter_watermark (struct dc_context const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dce_watermarks) ; 

__attribute__((used)) static void program_stutter_watermark_c(
	const struct dc_context *ctx,
	struct dce_watermarks marks)
{
	program_stutter_watermark(ctx,
			mmDPGV1_PIPE_STUTTER_CONTROL,
			mmDPGV1_WATERMARK_MASK_CONTROL,
			marks);
}