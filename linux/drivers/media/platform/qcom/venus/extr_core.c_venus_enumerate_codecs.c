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
typedef  scalar_t__ u32 ;
struct venus_inst {int /*<<< orphan*/  lock; scalar_t__ session_type; struct venus_core* core; } ;
struct venus_core {scalar_t__ dec_codecs; scalar_t__ enc_codecs; TYPE_1__* res; } ;
struct hfi_inst_ops {int dummy; } ;
struct TYPE_2__ {scalar_t__ hfi_version; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HFI_VERSION_1XX ; 
 unsigned int MAX_CODEC_NUM ; 
 scalar_t__ VIDC_SESSION_TYPE_DEC ; 
 int hfi_session_create (struct venus_inst*,struct hfi_inst_ops const*) ; 
 int hfi_session_deinit (struct venus_inst*) ; 
 int /*<<< orphan*/  hfi_session_destroy (struct venus_inst*) ; 
 int hfi_session_init (struct venus_inst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct venus_inst*) ; 
 struct venus_inst* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_v4l2_codec_type (scalar_t__) ; 

__attribute__((used)) static int venus_enumerate_codecs(struct venus_core *core, u32 type)
{
	const struct hfi_inst_ops dummy_ops = {};
	struct venus_inst *inst;
	u32 codec, codecs;
	unsigned int i;
	int ret;

	if (core->res->hfi_version != HFI_VERSION_1XX)
		return 0;

	inst = kzalloc(sizeof(*inst), GFP_KERNEL);
	if (!inst)
		return -ENOMEM;

	mutex_init(&inst->lock);
	inst->core = core;
	inst->session_type = type;
	if (type == VIDC_SESSION_TYPE_DEC)
		codecs = core->dec_codecs;
	else
		codecs = core->enc_codecs;

	ret = hfi_session_create(inst, &dummy_ops);
	if (ret)
		goto err;

	for (i = 0; i < MAX_CODEC_NUM; i++) {
		codec = (1UL << i) & codecs;
		if (!codec)
			continue;

		ret = hfi_session_init(inst, to_v4l2_codec_type(codec));
		if (ret)
			goto done;

		ret = hfi_session_deinit(inst);
		if (ret)
			goto done;
	}

done:
	hfi_session_destroy(inst);
err:
	mutex_destroy(&inst->lock);
	kfree(inst);

	return ret;
}