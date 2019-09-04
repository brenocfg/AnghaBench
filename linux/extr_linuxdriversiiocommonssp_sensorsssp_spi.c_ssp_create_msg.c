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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ssp_msg_header {int /*<<< orphan*/  data; void* options; void* length; int /*<<< orphan*/  cmd; } ;
struct ssp_msg {int length; int options; void* buffer; } ;

/* Variables and functions */
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SSP_HEADER_SIZE ; 
 int SSP_HEADER_SIZE_ALIGNED ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ssp_msg*) ; 
 void* kzalloc (int,int) ; 
 int /*<<< orphan*/  memcpy (void*,struct ssp_msg_header*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ssp_msg *ssp_create_msg(u8 cmd, u16 len, u16 opt, u32 data)
{
	struct ssp_msg_header h;
	struct ssp_msg *msg;

	msg = kzalloc(sizeof(*msg), GFP_KERNEL);
	if (!msg)
		return NULL;

	h.cmd = cmd;
	h.length = cpu_to_le16(len);
	h.options = cpu_to_le16(opt);
	h.data = cpu_to_le32(data);

	msg->buffer = kzalloc(SSP_HEADER_SIZE_ALIGNED + len,
			      GFP_KERNEL | GFP_DMA);
	if (!msg->buffer) {
		kfree(msg);
		return NULL;
	}

	msg->length = len;
	msg->options = opt;

	memcpy(msg->buffer, &h, SSP_HEADER_SIZE);

	return msg;
}