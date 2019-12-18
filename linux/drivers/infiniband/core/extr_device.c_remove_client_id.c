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
struct ib_client {int /*<<< orphan*/  client_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  clients ; 
 int /*<<< orphan*/  clients_rwsem ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ highest_client_id ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xa_load (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void remove_client_id(struct ib_client *client)
{
	down_write(&clients_rwsem);
	xa_erase(&clients, client->client_id);
	for (; highest_client_id; highest_client_id--)
		if (xa_load(&clients, highest_client_id - 1))
			break;
	up_write(&clients_rwsem);
}