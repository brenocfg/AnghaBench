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
typedef  int /*<<< orphan*/  u64 ;
struct zip_device {TYPE_1__* iq; } ;
struct TYPE_2__ {scalar_t__ sw_tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_CMD_QBUF_SIZE ; 
 int /*<<< orphan*/  free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_dbg (char*,scalar_t__) ; 

void zip_cmd_qbuf_free(struct zip_device *zip, int q)
{
	zip_dbg("Freeing cmd_qbuf 0x%lx\n", zip->iq[q].sw_tail);

	free_pages((u64)zip->iq[q].sw_tail, get_order(ZIP_CMD_QBUF_SIZE));
}