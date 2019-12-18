#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ diagass_support; } ;
struct TYPE_11__ {scalar_t__ supported_funcs; } ;
struct TYPE_10__ {scalar_t__ supported_funcs; } ;
struct TYPE_9__ {scalar_t__ supported_funcs; } ;
struct TYPE_8__ {scalar_t__ supported_funcs; } ;
struct TYPE_12__ {TYPE_4__ sbp; TYPE_3__ adp; TYPE_2__ ipa6; TYPE_1__ ipa4; } ;
struct qeth_card {TYPE_7__* gdev; TYPE_6__ info; TYPE_5__ options; scalar_t__ read_or_write_problem; int /*<<< orphan*/  force_alloc_skb; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  CARD_DEVID (struct qeth_card*) ; 
 int /*<<< orphan*/  CARD_RDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  CARD_WDEV (struct qeth_card*) ; 
 int EINTR ; 
 int ENETDOWN ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  IPA_IPV6 ; 
 int /*<<< orphan*/  IPA_SETADAPTERPARMS ; 
 int /*<<< orphan*/  IPA_SETADP_SET_DIAG_ASSIST ; 
 int /*<<< orphan*/  IS_IQD (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  QETH_PROT_IPV4 ; 
 int /*<<< orphan*/  QETH_PROT_IPV6 ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_set_offline (int /*<<< orphan*/ ) ; 
 int ccw_device_set_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qdio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_adp_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_determine_capabilities (struct qeth_card*) ; 
 int qeth_idx_activate_read_channel (struct qeth_card*) ; 
 int qeth_idx_activate_write_channel (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_init_func_level (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_init_tokens (struct qeth_card*) ; 
 scalar_t__ qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_mpc_initialize (struct qeth_card*) ; 
 int qeth_qdio_clear_card (struct qeth_card*,int) ; 
 int qeth_query_ipassists (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_query_setadapterparms (struct qeth_card*) ; 
 int qeth_query_setdiagass (struct qeth_card*) ; 
 int qeth_send_startlan (struct qeth_card*) ; 
 int qeth_update_from_chp_desc (struct qeth_card*) ; 

int qeth_core_hardsetup_card(struct qeth_card *card, bool *carrier_ok)
{
	int retries = 3;
	int rc;

	QETH_CARD_TEXT(card, 2, "hrdsetup");
	atomic_set(&card->force_alloc_skb, 0);
	rc = qeth_update_from_chp_desc(card);
	if (rc)
		return rc;
retry:
	if (retries < 3)
		QETH_DBF_MESSAGE(2, "Retrying to do IDX activates on device %x.\n",
				 CARD_DEVID(card));
	rc = qeth_qdio_clear_card(card, !IS_IQD(card));
	ccw_device_set_offline(CARD_DDEV(card));
	ccw_device_set_offline(CARD_WDEV(card));
	ccw_device_set_offline(CARD_RDEV(card));
	qdio_free(CARD_DDEV(card));
	rc = ccw_device_set_online(CARD_RDEV(card));
	if (rc)
		goto retriable;
	rc = ccw_device_set_online(CARD_WDEV(card));
	if (rc)
		goto retriable;
	rc = ccw_device_set_online(CARD_DDEV(card));
	if (rc)
		goto retriable;
retriable:
	if (rc == -ERESTARTSYS) {
		QETH_CARD_TEXT(card, 2, "break1");
		return rc;
	} else if (rc) {
		QETH_CARD_TEXT_(card, 2, "1err%d", rc);
		if (--retries < 0)
			goto out;
		else
			goto retry;
	}
	qeth_determine_capabilities(card);
	qeth_init_tokens(card);
	qeth_init_func_level(card);

	rc = qeth_idx_activate_read_channel(card);
	if (rc == -EINTR) {
		QETH_CARD_TEXT(card, 2, "break2");
		return rc;
	} else if (rc) {
		QETH_CARD_TEXT_(card, 2, "3err%d", rc);
		if (--retries < 0)
			goto out;
		else
			goto retry;
	}

	rc = qeth_idx_activate_write_channel(card);
	if (rc == -EINTR) {
		QETH_CARD_TEXT(card, 2, "break3");
		return rc;
	} else if (rc) {
		QETH_CARD_TEXT_(card, 2, "4err%d", rc);
		if (--retries < 0)
			goto out;
		else
			goto retry;
	}
	card->read_or_write_problem = 0;
	rc = qeth_mpc_initialize(card);
	if (rc) {
		QETH_CARD_TEXT_(card, 2, "5err%d", rc);
		goto out;
	}

	rc = qeth_send_startlan(card);
	if (rc) {
		QETH_CARD_TEXT_(card, 2, "6err%d", rc);
		if (rc == -ENETDOWN) {
			dev_warn(&card->gdev->dev, "The LAN is offline\n");
			*carrier_ok = false;
		} else {
			goto out;
		}
	} else {
		*carrier_ok = true;
	}

	card->options.ipa4.supported_funcs = 0;
	card->options.ipa6.supported_funcs = 0;
	card->options.adp.supported_funcs = 0;
	card->options.sbp.supported_funcs = 0;
	card->info.diagass_support = 0;
	rc = qeth_query_ipassists(card, QETH_PROT_IPV4);
	if (rc == -ENOMEM)
		goto out;
	if (qeth_is_supported(card, IPA_IPV6)) {
		rc = qeth_query_ipassists(card, QETH_PROT_IPV6);
		if (rc == -ENOMEM)
			goto out;
	}
	if (qeth_is_supported(card, IPA_SETADAPTERPARMS)) {
		rc = qeth_query_setadapterparms(card);
		if (rc < 0) {
			QETH_CARD_TEXT_(card, 2, "7err%d", rc);
			goto out;
		}
	}
	if (qeth_adp_supported(card, IPA_SETADP_SET_DIAG_ASSIST)) {
		rc = qeth_query_setdiagass(card);
		if (rc < 0) {
			QETH_CARD_TEXT_(card, 2, "8err%d", rc);
			goto out;
		}
	}
	return 0;
out:
	dev_warn(&card->gdev->dev, "The qeth device driver failed to recover "
		"an error on the device\n");
	QETH_DBF_MESSAGE(2, "Initialization for device %x failed in hardsetup! rc=%d\n",
			 CARD_DEVID(card), rc);
	return rc;
}