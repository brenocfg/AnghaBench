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
struct stream_encoder {int dummy; } ;
struct dc_context {int dummy; } ;
struct dc_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct stream_encoder*) ; 
 struct stream_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ virtual_stream_encoder_construct (struct stream_encoder*,struct dc_context*,struct dc_bios*) ; 

struct stream_encoder *virtual_stream_encoder_create(
	struct dc_context *ctx, struct dc_bios *bp)
{
	struct stream_encoder *enc = kzalloc(sizeof(*enc), GFP_KERNEL);

	if (!enc)
		return NULL;

	if (virtual_stream_encoder_construct(enc, ctx, bp))
		return enc;

	BREAK_TO_DEBUGGER();
	kfree(enc);
	return NULL;
}