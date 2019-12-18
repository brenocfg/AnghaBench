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
typedef  int u8 ;
struct TYPE_2__ {struct b43_pio_txqueue* tx_queue_AC_BE; struct b43_pio_txqueue* tx_queue_AC_BK; struct b43_pio_txqueue* tx_queue_AC_VI; struct b43_pio_txqueue* tx_queue_AC_VO; } ;
struct b43_wldev {TYPE_1__ pio; scalar_t__ qos_enabled; } ;
struct b43_pio_txqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 

__attribute__((used)) static struct b43_pio_txqueue *select_queue_by_priority(struct b43_wldev *dev,
							u8 queue_prio)
{
	struct b43_pio_txqueue *q;

	if (dev->qos_enabled) {
		/* 0 = highest priority */
		switch (queue_prio) {
		default:
			B43_WARN_ON(1);
			/* fallthrough */
		case 0:
			q = dev->pio.tx_queue_AC_VO;
			break;
		case 1:
			q = dev->pio.tx_queue_AC_VI;
			break;
		case 2:
			q = dev->pio.tx_queue_AC_BE;
			break;
		case 3:
			q = dev->pio.tx_queue_AC_BK;
			break;
		}
	} else
		q = dev->pio.tx_queue_AC_BE;

	return q;
}