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
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
struct lanai_vcc {TYPE_1__ rx; } ;
struct lanai_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_sdu; } ;
struct atm_qos {TYPE_2__ rxtp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAL5_RX_MULTIPLIER ; 
 int lanai_get_sized_buffer (struct lanai_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int lanai_setup_rx_vci_aal5(struct lanai_dev *lanai,
	struct lanai_vcc *lvcc, const struct atm_qos *qos)
{
	return lanai_get_sized_buffer(lanai, &lvcc->rx.buf,
	    qos->rxtp.max_sdu, AAL5_RX_MULTIPLIER, "RX");
}