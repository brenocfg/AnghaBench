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
struct resp_desc {int numDesc; scalar_t__ cmd; scalar_t__ parm1; int /*<<< orphan*/  parm3; int /*<<< orphan*/  parm2; int /*<<< orphan*/  flags; scalar_t__ seqNo; } ;
typedef  struct resp_desc u8 ;
typedef  scalar_t__ u32 ;
struct typhoon_indexes {int /*<<< orphan*/  respCleared; int /*<<< orphan*/  respReady; } ;
struct TYPE_2__ {struct resp_desc* ringBase; } ;
struct typhoon {int /*<<< orphan*/  dev; TYPE_1__ respRing; struct typhoon_indexes* indexes; } ;

/* Variables and functions */
 scalar_t__ RESPONSE_RING_SIZE ; 
 scalar_t__ TYPHOON_CMD_HELLO_RESP ; 
 scalar_t__ TYPHOON_CMD_READ_MEDIA_STATUS ; 
 int /*<<< orphan*/  TYPHOON_RESP_ERROR ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct resp_desc*,struct resp_desc*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  typhoon_hello (struct typhoon*) ; 
 int /*<<< orphan*/  typhoon_inc_resp_index (scalar_t__*,int) ; 
 int /*<<< orphan*/  typhoon_media_status (int /*<<< orphan*/ ,struct resp_desc*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
typhoon_process_response(struct typhoon *tp, int resp_size,
				struct resp_desc *resp_save)
{
	struct typhoon_indexes *indexes = tp->indexes;
	struct resp_desc *resp;
	u8 *base = tp->respRing.ringBase;
	int count, len, wrap_len;
	u32 cleared;
	u32 ready;

	cleared = le32_to_cpu(indexes->respCleared);
	ready = le32_to_cpu(indexes->respReady);
	while(cleared != ready) {
		resp = (struct resp_desc *)(base + cleared);
		count = resp->numDesc + 1;
		if(resp_save && resp->seqNo) {
			if(count > resp_size) {
				resp_save->flags = TYPHOON_RESP_ERROR;
				goto cleanup;
			}

			wrap_len = 0;
			len = count * sizeof(*resp);
			if(unlikely(cleared + len > RESPONSE_RING_SIZE)) {
				wrap_len = cleared + len - RESPONSE_RING_SIZE;
				len = RESPONSE_RING_SIZE - cleared;
			}

			memcpy(resp_save, resp, len);
			if(unlikely(wrap_len)) {
				resp_save += len / sizeof(*resp);
				memcpy(resp_save, base, wrap_len);
			}

			resp_save = NULL;
		} else if(resp->cmd == TYPHOON_CMD_READ_MEDIA_STATUS) {
			typhoon_media_status(tp->dev, resp);
		} else if(resp->cmd == TYPHOON_CMD_HELLO_RESP) {
			typhoon_hello(tp);
		} else {
			netdev_err(tp->dev,
				   "dumping unexpected response 0x%04x:%d:0x%02x:0x%04x:%08x:%08x\n",
				   le16_to_cpu(resp->cmd),
				   resp->numDesc, resp->flags,
				   le16_to_cpu(resp->parm1),
				   le32_to_cpu(resp->parm2),
				   le32_to_cpu(resp->parm3));
		}

cleanup:
		typhoon_inc_resp_index(&cleared, count);
	}

	indexes->respCleared = cpu_to_le32(cleared);
	wmb();
	return resp_save == NULL;
}