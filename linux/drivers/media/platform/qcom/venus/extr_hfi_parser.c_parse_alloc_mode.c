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
typedef  scalar_t__ u32 ;
struct venus_core {int /*<<< orphan*/  caps; } ;
struct hfi_buffer_alloc_mode_supported {scalar_t__ num_entries; scalar_t__ buffer_type; scalar_t__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ HFI_BUFFER_OUTPUT ; 
 scalar_t__ HFI_BUFFER_OUTPUT2 ; 
 scalar_t__ MAX_ALLOC_MODE_ENTRIES ; 
 int /*<<< orphan*/  fill_buf_mode ; 
 int /*<<< orphan*/  for_each_codec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void
parse_alloc_mode(struct venus_core *core, u32 codecs, u32 domain, void *data)
{
	struct hfi_buffer_alloc_mode_supported *mode = data;
	u32 num_entries = mode->num_entries;
	u32 *type;

	if (num_entries > MAX_ALLOC_MODE_ENTRIES)
		return;

	type = mode->data;

	while (num_entries--) {
		if (mode->buffer_type == HFI_BUFFER_OUTPUT ||
		    mode->buffer_type == HFI_BUFFER_OUTPUT2)
			for_each_codec(core->caps, ARRAY_SIZE(core->caps),
				       codecs, domain, fill_buf_mode, type, 1);

		type++;
	}
}