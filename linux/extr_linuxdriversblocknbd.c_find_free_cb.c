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
struct nbd_device {int /*<<< orphan*/  config_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_free_cb(int id, void *ptr, void *data)
{
	struct nbd_device *nbd = ptr;
	struct nbd_device **found = data;

	if (!refcount_read(&nbd->config_refs)) {
		*found = nbd;
		return 1;
	}
	return 0;
}