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
struct tg3 {int irq_cnt; TYPE_1__* napi; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tg3_poll ; 
 int /*<<< orphan*/  tg3_poll_msix ; 

__attribute__((used)) static void tg3_napi_init(struct tg3 *tp)
{
	int i;

	netif_napi_add(tp->dev, &tp->napi[0].napi, tg3_poll, 64);
	for (i = 1; i < tp->irq_cnt; i++)
		netif_napi_add(tp->dev, &tp->napi[i].napi, tg3_poll_msix, 64);
}