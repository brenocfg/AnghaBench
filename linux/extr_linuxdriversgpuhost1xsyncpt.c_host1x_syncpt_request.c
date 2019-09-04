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
struct host1x_syncpt {int dummy; } ;
struct host1x_client {TYPE_1__* parent; } ;
struct host1x {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct host1x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct host1x_syncpt* host1x_syncpt_alloc (struct host1x*,struct host1x_client*,unsigned long) ; 

struct host1x_syncpt *host1x_syncpt_request(struct host1x_client *client,
					    unsigned long flags)
{
	struct host1x *host = dev_get_drvdata(client->parent->parent);

	return host1x_syncpt_alloc(host, client, flags);
}