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
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  image_update_buffer; scalar_t__ entry_created; } ;

/* Variables and functions */
 int /*<<< orphan*/  image_type ; 
 int /*<<< orphan*/  img_update_realloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_empty_list () ; 
 scalar_t__ packetize_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 TYPE_1__ rbu_data ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void callbackfn_rbu(const struct firmware *fw, void *context)
{
	rbu_data.entry_created = 0;

	if (!fw)
		return;

	if (!fw->size)
		goto out;

	spin_lock(&rbu_data.lock);
	if (!strcmp(image_type, "mono")) {
		if (!img_update_realloc(fw->size))
			memcpy(rbu_data.image_update_buffer,
				fw->data, fw->size);
	} else if (!strcmp(image_type, "packet")) {
		/*
		 * we need to free previous packets if a
		 * new hunk of packets needs to be downloaded
		 */
		packet_empty_list();
		if (packetize_data(fw->data, fw->size))
			/* Incase something goes wrong when we are
			 * in middle of packetizing the data, we
			 * need to free up whatever packets might
			 * have been created before we quit.
			 */
			packet_empty_list();
	} else
		pr_debug("invalid image type specified.\n");
	spin_unlock(&rbu_data.lock);
 out:
	release_firmware(fw);
}