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
struct link_encoder {int dummy; } ;
struct encoder_init_data {size_t transmitter; int channel; size_t hpd_source; } ;
struct dcn10_link_encoder {struct link_encoder base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dcn10_link_encoder_construct (struct dcn10_link_encoder*,struct encoder_init_data const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dcn10_link_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_mask ; 
 int /*<<< orphan*/  le_shift ; 
 int /*<<< orphan*/ * link_enc_aux_regs ; 
 int /*<<< orphan*/  link_enc_feature ; 
 int /*<<< orphan*/ * link_enc_hpd_regs ; 
 int /*<<< orphan*/ * link_enc_regs ; 

struct link_encoder *dcn10_link_encoder_create(
	const struct encoder_init_data *enc_init_data)
{
	struct dcn10_link_encoder *enc10 =
		kzalloc(sizeof(struct dcn10_link_encoder), GFP_KERNEL);

	if (!enc10)
		return NULL;

	dcn10_link_encoder_construct(enc10,
				      enc_init_data,
				      &link_enc_feature,
				      &link_enc_regs[enc_init_data->transmitter],
				      &link_enc_aux_regs[enc_init_data->channel - 1],
				      &link_enc_hpd_regs[enc_init_data->hpd_source],
				      &le_shift,
				      &le_mask);

	return &enc10->base;
}