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
struct scif_client {int /*<<< orphan*/  si; } ;

/* Variables and functions */
 int /*<<< orphan*/  subsys_interface_unregister (int /*<<< orphan*/ *) ; 

void scif_client_unregister(struct scif_client *client)
{
	subsys_interface_unregister(&client->si);
}