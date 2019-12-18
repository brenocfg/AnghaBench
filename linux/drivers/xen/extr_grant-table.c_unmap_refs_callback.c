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
struct unmap_refs_callback_data {int result; int /*<<< orphan*/  completion; } ;
struct gntab_unmap_queue_data {struct unmap_refs_callback_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unmap_refs_callback(int result,
		struct gntab_unmap_queue_data *data)
{
	struct unmap_refs_callback_data *d = data->data;

	d->result = result;
	complete(&d->completion);
}