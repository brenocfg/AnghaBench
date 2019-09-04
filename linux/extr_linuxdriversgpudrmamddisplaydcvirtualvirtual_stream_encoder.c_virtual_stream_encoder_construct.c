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
struct stream_encoder {struct dc_bios* bp; int /*<<< orphan*/  id; struct dc_context* ctx; int /*<<< orphan*/ * funcs; } ;
struct dc_context {int dummy; } ;
struct dc_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_ID_VIRTUAL ; 
 int /*<<< orphan*/  virtual_str_enc_funcs ; 

bool virtual_stream_encoder_construct(
	struct stream_encoder *enc,
	struct dc_context *ctx,
	struct dc_bios *bp)
{
	if (!enc)
		return false;
	if (!bp)
		return false;

	enc->funcs = &virtual_str_enc_funcs;
	enc->ctx = ctx;
	enc->id = ENGINE_ID_VIRTUAL;
	enc->bp = bp;

	return true;
}