#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qeth_card {int /*<<< orphan*/  rx_mode_work; int /*<<< orphan*/  mac_htable; } ;
struct TYPE_3__ {int /*<<< orphan*/ * type; } ;
struct ccwgroup_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qeth_card* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_generic_devtype ; 
 int qeth_l2_create_device_attributes (TYPE_1__*) ; 
 int /*<<< orphan*/  qeth_l2_rx_mode_work ; 
 int /*<<< orphan*/  qeth_l2_vnicc_set_defaults (struct qeth_card*) ; 

__attribute__((used)) static int qeth_l2_probe_device(struct ccwgroup_device *gdev)
{
	struct qeth_card *card = dev_get_drvdata(&gdev->dev);
	int rc;

	qeth_l2_vnicc_set_defaults(card);

	if (gdev->dev.type == &qeth_generic_devtype) {
		rc = qeth_l2_create_device_attributes(&gdev->dev);
		if (rc)
			return rc;
	}

	hash_init(card->mac_htable);
	INIT_WORK(&card->rx_mode_work, qeth_l2_rx_mode_work);
	return 0;
}