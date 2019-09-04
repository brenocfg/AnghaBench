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
struct link_encoder {int /*<<< orphan*/  preferred_engine; int /*<<< orphan*/  output_signals; int /*<<< orphan*/  transmitter; int /*<<< orphan*/  connector; int /*<<< orphan*/  hpd_source; int /*<<< orphan*/  id; int /*<<< orphan*/  ctx; int /*<<< orphan*/ * funcs; } ;
struct encoder_init_data {int /*<<< orphan*/  transmitter; int /*<<< orphan*/  connector; int /*<<< orphan*/  hpd_source; int /*<<< orphan*/  encoder; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_ID_VIRTUAL ; 
 int /*<<< orphan*/  SIGNAL_TYPE_VIRTUAL ; 
 int /*<<< orphan*/  virtual_lnk_enc_funcs ; 

bool virtual_link_encoder_construct(
	struct link_encoder *enc, const struct encoder_init_data *init_data)
{
	enc->funcs = &virtual_lnk_enc_funcs;
	enc->ctx = init_data->ctx;
	enc->id = init_data->encoder;

	enc->hpd_source = init_data->hpd_source;
	enc->connector = init_data->connector;

	enc->transmitter = init_data->transmitter;

	enc->output_signals = SIGNAL_TYPE_VIRTUAL;

	enc->preferred_engine = ENGINE_ID_VIRTUAL;

	return true;
}