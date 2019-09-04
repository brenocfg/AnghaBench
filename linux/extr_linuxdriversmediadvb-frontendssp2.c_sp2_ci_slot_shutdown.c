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
struct sp2 {TYPE_1__* client; } ;
struct dvb_ca_en50221 {struct sp2* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

int sp2_ci_slot_shutdown(struct dvb_ca_en50221 *en50221, int slot)
{
	struct sp2 *s = en50221->data;

	dev_dbg(&s->client->dev, "slot:%d\n", slot);

	/* not implemented */
	return 0;
}