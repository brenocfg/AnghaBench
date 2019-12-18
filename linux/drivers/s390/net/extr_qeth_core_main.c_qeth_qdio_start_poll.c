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
struct qeth_card {int /*<<< orphan*/  napi; TYPE_1__* dev; } ;
struct ccw_device {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_qdio_start_poll(struct ccw_device *ccwdev, int queue,
				 unsigned long card_ptr)
{
	struct qeth_card *card = (struct qeth_card *)card_ptr;

	if (card->dev->flags & IFF_UP)
		napi_schedule(&card->napi);
}