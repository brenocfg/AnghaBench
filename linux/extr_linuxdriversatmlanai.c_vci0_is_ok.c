#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lanai_dev {scalar_t__ naal0; int /*<<< orphan*/  conf2; } ;
struct TYPE_4__ {scalar_t__ traffic_class; } ;
struct TYPE_3__ {scalar_t__ traffic_class; } ;
struct atm_qos {scalar_t__ aal; TYPE_2__ rxtp; TYPE_1__ txtp; } ;

/* Variables and functions */
 scalar_t__ ATM_AAL0 ; 
 scalar_t__ ATM_CBR ; 
 scalar_t__ ATM_NONE ; 
 int /*<<< orphan*/  CONFIG2_VCI0_NORMAL ; 
 int /*<<< orphan*/  conf2_write_if_powerup (struct lanai_dev*) ; 

__attribute__((used)) static inline int vci0_is_ok(struct lanai_dev *lanai,
	const struct atm_qos *qos)
{
	if (qos->txtp.traffic_class == ATM_CBR || qos->aal == ATM_AAL0)
		return 0;
	if (qos->rxtp.traffic_class != ATM_NONE) {
		if (lanai->naal0 != 0)
			return 0;
		lanai->conf2 |= CONFIG2_VCI0_NORMAL;
		conf2_write_if_powerup(lanai);
	}
	return 1;
}