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
struct venus_buffer {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  size; } ;
struct hfi_buffer_desc {int num_buffers; int response_required; int /*<<< orphan*/  device_addr; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buffer_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_BUFFER_OUTPUT ; 
 int /*<<< orphan*/  memset (struct hfi_buffer_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_buffer_desc(const struct venus_buffer *buf,
			     struct hfi_buffer_desc *bd, bool response)
{
	memset(bd, 0, sizeof(*bd));
	bd->buffer_type = HFI_BUFFER_OUTPUT;
	bd->buffer_size = buf->size;
	bd->num_buffers = 1;
	bd->device_addr = buf->dma_addr;
	bd->response_required = response;
}