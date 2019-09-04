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
struct TYPE_2__ {scalar_t__ next; } ;
struct smscore_device_t {TYPE_1__ clients; } ;
struct smscore_client_t {int /*<<< orphan*/  context; int /*<<< orphan*/  (* onremove_handler ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smscore_notify_clients(struct smscore_device_t *coredev)
{
	struct smscore_client_t *client;

	/* the client must call smscore_unregister_client from remove handler */
	while (!list_empty(&coredev->clients)) {
		client = (struct smscore_client_t *) coredev->clients.next;
		client->onremove_handler(client->context);
	}
}