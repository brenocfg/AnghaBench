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
struct dasd_uid {int /*<<< orphan*/  serial; int /*<<< orphan*/  vendor; } ;
struct TYPE_2__ {int /*<<< orphan*/  serial; int /*<<< orphan*/  vendor; } ;
struct alias_server {int /*<<< orphan*/  lculist; int /*<<< orphan*/  server; TYPE_1__ uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct alias_server* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct alias_server* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct alias_server *_allocate_server(struct dasd_uid *uid)
{
	struct alias_server *server;

	server = kzalloc(sizeof(*server), GFP_KERNEL);
	if (!server)
		return ERR_PTR(-ENOMEM);
	memcpy(server->uid.vendor, uid->vendor, sizeof(uid->vendor));
	memcpy(server->uid.serial, uid->serial, sizeof(uid->serial));
	INIT_LIST_HEAD(&server->server);
	INIT_LIST_HEAD(&server->lculist);
	return server;
}