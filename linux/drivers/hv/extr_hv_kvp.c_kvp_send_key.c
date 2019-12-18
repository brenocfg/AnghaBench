#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct work_struct {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  index; } ;
struct TYPE_15__ {scalar_t__ key; int /*<<< orphan*/  key_size; } ;
struct TYPE_13__ {scalar_t__ key; int /*<<< orphan*/  key_size; } ;
struct TYPE_14__ {TYPE_4__ data; } ;
struct TYPE_11__ {int value_u32; int value_u64; scalar_t__ key; int /*<<< orphan*/  key_size; scalar_t__ value; int /*<<< orphan*/  value_size; int /*<<< orphan*/  value_type; } ;
struct TYPE_12__ {TYPE_2__ data; } ;
struct TYPE_17__ {TYPE_7__ kvp_enum_data; TYPE_6__ kvp_delete; TYPE_5__ kvp_get; TYPE_3__ kvp_set; } ;
struct TYPE_10__ {int operation; void* pool; } ;
struct hv_kvp_msg {TYPE_8__ body; TYPE_1__ kvp_hdr; } ;
typedef  void* __u8 ;
typedef  int __u64 ;
typedef  int __u32 ;
struct TYPE_18__ {scalar_t__ state; struct hv_kvp_msg* kvp_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HVUTIL_HOSTMSG_RECEIVED ; 
 scalar_t__ HVUTIL_READY ; 
 scalar_t__ HVUTIL_USERSPACE_REQ ; 
 int /*<<< orphan*/  HV_E_FAIL ; 
 int /*<<< orphan*/  HV_KVP_EXCHANGE_MAX_KEY_SIZE ; 
 int /*<<< orphan*/  HV_KVP_EXCHANGE_MAX_VALUE_SIZE ; 
#define  KVP_OP_DELETE 136 
#define  KVP_OP_ENUMERATE 135 
#define  KVP_OP_GET 134 
#define  KVP_OP_GET_IP_INFO 133 
#define  KVP_OP_SET 132 
#define  KVP_OP_SET_IP_INFO 131 
#define  REG_SZ 130 
#define  REG_U32 129 
#define  REG_U64 128 
 int /*<<< orphan*/  UTF16_LITTLE_ENDIAN ; 
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hvt ; 
 int hvutil_transport_send (int /*<<< orphan*/ ,struct hv_kvp_msg*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hv_kvp_msg*) ; 
 int /*<<< orphan*/  kvp_respond_to_host (struct hv_kvp_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvp_timeout_work ; 
 TYPE_9__ kvp_transaction ; 
 struct hv_kvp_msg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  process_ib_ipinfo (struct hv_kvp_msg*,struct hv_kvp_msg*,int const) ; 
 int /*<<< orphan*/  sprintf (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  utf16s_to_utf8s (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kvp_send_key(struct work_struct *dummy)
{
	struct hv_kvp_msg *message;
	struct hv_kvp_msg *in_msg;
	__u8 operation = kvp_transaction.kvp_msg->kvp_hdr.operation;
	__u8 pool = kvp_transaction.kvp_msg->kvp_hdr.pool;
	__u32 val32;
	__u64 val64;
	int rc;

	/* The transaction state is wrong. */
	if (kvp_transaction.state != HVUTIL_HOSTMSG_RECEIVED)
		return;

	message = kzalloc(sizeof(*message), GFP_KERNEL);
	if (!message)
		return;

	message->kvp_hdr.operation = operation;
	message->kvp_hdr.pool = pool;
	in_msg = kvp_transaction.kvp_msg;

	/*
	 * The key/value strings sent from the host are encoded in
	 * in utf16; convert it to utf8 strings.
	 * The host assures us that the utf16 strings will not exceed
	 * the max lengths specified. We will however, reserve room
	 * for the string terminating character - in the utf16s_utf8s()
	 * function we limit the size of the buffer where the converted
	 * string is placed to HV_KVP_EXCHANGE_MAX_*_SIZE -1 to guarantee
	 * that the strings can be properly terminated!
	 */

	switch (message->kvp_hdr.operation) {
	case KVP_OP_SET_IP_INFO:
		process_ib_ipinfo(in_msg, message, KVP_OP_SET_IP_INFO);
		break;
	case KVP_OP_GET_IP_INFO:
		/*
		 * We only need to pass on the info of operation, adapter_id
		 * and addr_family to the userland kvp daemon.
		 */
		process_ib_ipinfo(in_msg, message, KVP_OP_GET_IP_INFO);
		break;
	case KVP_OP_SET:
		switch (in_msg->body.kvp_set.data.value_type) {
		case REG_SZ:
			/*
			 * The value is a string - utf16 encoding.
			 */
			message->body.kvp_set.data.value_size =
				utf16s_to_utf8s(
				(wchar_t *)in_msg->body.kvp_set.data.value,
				in_msg->body.kvp_set.data.value_size,
				UTF16_LITTLE_ENDIAN,
				message->body.kvp_set.data.value,
				HV_KVP_EXCHANGE_MAX_VALUE_SIZE - 1) + 1;
			break;

		case REG_U32:
			/*
			 * The value is a 32 bit scalar.
			 * We save this as a utf8 string.
			 */
			val32 = in_msg->body.kvp_set.data.value_u32;
			message->body.kvp_set.data.value_size =
				sprintf(message->body.kvp_set.data.value,
					"%u", val32) + 1;
			break;

		case REG_U64:
			/*
			 * The value is a 64 bit scalar.
			 * We save this as a utf8 string.
			 */
			val64 = in_msg->body.kvp_set.data.value_u64;
			message->body.kvp_set.data.value_size =
				sprintf(message->body.kvp_set.data.value,
					"%llu", val64) + 1;
			break;

		}

		/*
		 * The key is always a string - utf16 encoding.
		 */
		message->body.kvp_set.data.key_size =
			utf16s_to_utf8s(
			(wchar_t *)in_msg->body.kvp_set.data.key,
			in_msg->body.kvp_set.data.key_size,
			UTF16_LITTLE_ENDIAN,
			message->body.kvp_set.data.key,
			HV_KVP_EXCHANGE_MAX_KEY_SIZE - 1) + 1;

		break;

	case KVP_OP_GET:
		message->body.kvp_get.data.key_size =
			utf16s_to_utf8s(
			(wchar_t *)in_msg->body.kvp_get.data.key,
			in_msg->body.kvp_get.data.key_size,
			UTF16_LITTLE_ENDIAN,
			message->body.kvp_get.data.key,
			HV_KVP_EXCHANGE_MAX_KEY_SIZE - 1) + 1;
		break;

	case KVP_OP_DELETE:
		message->body.kvp_delete.key_size =
			utf16s_to_utf8s(
			(wchar_t *)in_msg->body.kvp_delete.key,
			in_msg->body.kvp_delete.key_size,
			UTF16_LITTLE_ENDIAN,
			message->body.kvp_delete.key,
			HV_KVP_EXCHANGE_MAX_KEY_SIZE - 1) + 1;
		break;

	case KVP_OP_ENUMERATE:
		message->body.kvp_enum_data.index =
			in_msg->body.kvp_enum_data.index;
		break;
	}

	kvp_transaction.state = HVUTIL_USERSPACE_REQ;
	rc = hvutil_transport_send(hvt, message, sizeof(*message), NULL);
	if (rc) {
		pr_debug("KVP: failed to communicate to the daemon: %d\n", rc);
		if (cancel_delayed_work_sync(&kvp_timeout_work)) {
			kvp_respond_to_host(message, HV_E_FAIL);
			kvp_transaction.state = HVUTIL_READY;
		}
	}

	kfree(message);
}