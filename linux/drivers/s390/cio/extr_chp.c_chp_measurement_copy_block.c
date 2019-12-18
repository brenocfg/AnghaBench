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
struct cmg_entry {scalar_t__* values; } ;
struct chp_id {int id; } ;
struct channel_subsystem {void* cub_addr2; void* cub_addr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct cmg_entry*,struct cmg_entry*,int) ; 

__attribute__((used)) static void chp_measurement_copy_block(struct cmg_entry *buf,
				       struct channel_subsystem *css,
				       struct chp_id chpid)
{
	void *area;
	struct cmg_entry *entry, reference_buf;
	int idx;

	if (chpid.id < 128) {
		area = css->cub_addr1;
		idx = chpid.id;
	} else {
		area = css->cub_addr2;
		idx = chpid.id - 128;
	}
	entry = area + (idx * sizeof(struct cmg_entry));
	do {
		memcpy(buf, entry, sizeof(*entry));
		memcpy(&reference_buf, entry, sizeof(*entry));
	} while (reference_buf.values[0] != buf->values[0]);
}