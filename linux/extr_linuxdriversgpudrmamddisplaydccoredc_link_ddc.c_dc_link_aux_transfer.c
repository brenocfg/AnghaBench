#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ddc_service {TYPE_3__* ctx; struct ddc* ddc_pin; } ;
struct ddc {TYPE_4__* pin_data; } ;
struct aux_request_transaction_data {int type; int action; unsigned int address; unsigned int length; void* data; scalar_t__ delay; } ;
struct aux_reply_transaction_data {int type; int action; unsigned int address; unsigned int length; void* data; scalar_t__ delay; } ;
struct aux_engine {TYPE_5__* funcs; } ;
typedef  enum i2caux_transaction_action { ____Placeholder_i2caux_transaction_action } i2caux_transaction_action ;
typedef  enum aux_transaction_type { ____Placeholder_aux_transaction_type } aux_transaction_type ;
typedef  enum aux_channel_operation_result { ____Placeholder_aux_channel_operation_result } aux_channel_operation_result ;
typedef  int /*<<< orphan*/  aux_req ;
typedef  int /*<<< orphan*/  aux_rep ;
struct TYPE_10__ {int (* get_channel_status ) (struct aux_engine*,int*) ;int (* read_channel_reply ) (struct aux_engine*,unsigned int,void*,int*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* release_engine ) (struct aux_engine*) ;int /*<<< orphan*/  (* submit_channel_request ) (struct aux_engine*,struct aux_request_transaction_data*) ;int /*<<< orphan*/  (* acquire ) (struct aux_engine*,struct ddc*) ;} ;
struct TYPE_9__ {size_t en; } ;
struct TYPE_8__ {TYPE_2__* dc; } ;
struct TYPE_7__ {TYPE_1__* res_pool; } ;
struct TYPE_6__ {struct aux_engine** engines; } ;

/* Variables and functions */
#define  AUX_CHANNEL_OPERATION_FAILED_HPD_DISCON 132 
#define  AUX_CHANNEL_OPERATION_FAILED_INVALID_REPLY 131 
#define  AUX_CHANNEL_OPERATION_FAILED_REASON_UNKNOWN 130 
#define  AUX_CHANNEL_OPERATION_FAILED_TIMEOUT 129 
#define  AUX_CHANNEL_OPERATION_SUCCEEDED 128 
 int /*<<< orphan*/  memset (struct aux_request_transaction_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct aux_engine*,struct ddc*) ; 
 int /*<<< orphan*/  stub2 (struct aux_engine*,struct aux_request_transaction_data*) ; 
 int stub3 (struct aux_engine*,int*) ; 
 int stub4 (struct aux_engine*,unsigned int,void*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (struct aux_engine*) ; 

int dc_link_aux_transfer(struct ddc_service *ddc,
			     unsigned int address,
			     uint8_t *reply,
			     void *buffer,
			     unsigned int size,
			     enum aux_transaction_type type,
			     enum i2caux_transaction_action action)
{
	struct ddc *ddc_pin = ddc->ddc_pin;
	struct aux_engine *aux_engine;
	enum aux_channel_operation_result operation_result;
	struct aux_request_transaction_data aux_req;
	struct aux_reply_transaction_data aux_rep;
	uint8_t returned_bytes = 0;
	int res = -1;
	uint32_t status;

	memset(&aux_req, 0, sizeof(aux_req));
	memset(&aux_rep, 0, sizeof(aux_rep));

	aux_engine = ddc->ctx->dc->res_pool->engines[ddc_pin->pin_data->en];
	aux_engine->funcs->acquire(aux_engine, ddc_pin);

	aux_req.type = type;
	aux_req.action = action;

	aux_req.address = address;
	aux_req.delay = 0;
	aux_req.length = size;
	aux_req.data = buffer;

	aux_engine->funcs->submit_channel_request(aux_engine, &aux_req);
	operation_result = aux_engine->funcs->get_channel_status(aux_engine, &returned_bytes);

	switch (operation_result) {
	case AUX_CHANNEL_OPERATION_SUCCEEDED:
		res = returned_bytes;

		if (res <= size && res >= 0)
			res = aux_engine->funcs->read_channel_reply(aux_engine, size,
								buffer, reply,
								&status);

		break;
	case AUX_CHANNEL_OPERATION_FAILED_HPD_DISCON:
		res = 0;
		break;
	case AUX_CHANNEL_OPERATION_FAILED_REASON_UNKNOWN:
	case AUX_CHANNEL_OPERATION_FAILED_INVALID_REPLY:
	case AUX_CHANNEL_OPERATION_FAILED_TIMEOUT:
		res = -1;
		break;
	}
	aux_engine->funcs->release_engine(aux_engine);
	return res;
}