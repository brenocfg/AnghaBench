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
struct mbox_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void mbox_test_message_sent(struct mbox_client *client,
				   void *message, int r)
{
	if (r)
		dev_warn(client->dev,
			 "Client: Message could not be sent: %d\n", r);
	else
		dev_info(client->dev,
			 "Client: Message sent\n");
}