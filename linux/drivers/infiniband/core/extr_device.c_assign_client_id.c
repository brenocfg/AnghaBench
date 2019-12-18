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
 int /*<<< orphan*/  CLIENT_REGISTERED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clients ; 
 int /*<<< orphan*/  clients_rwsem ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  highest_client_id ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int xa_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ib_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int assign_client_id(struct ib_client *client)
{
	int ret;

	down_write(&clients_rwsem);
	/*
	 * The add/remove callbacks must be called in FIFO/LIFO order. To
	 * achieve this we assign client_ids so they are sorted in
	 * registration order.
	 */
	client->client_id = highest_client_id;
	ret = xa_insert(&clients, client->client_id, client, GFP_KERNEL);
	if (ret)
		goto out;

	highest_client_id++;
	xa_set_mark(&clients, client->client_id, CLIENT_REGISTERED);

out:
	up_write(&clients_rwsem);
	return ret;
}