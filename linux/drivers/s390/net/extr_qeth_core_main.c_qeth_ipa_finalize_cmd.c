#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qeth_cmd_buffer {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ipa; } ;
struct qeth_card {TYPE_2__ seqno; } ;
struct TYPE_4__ {scalar_t__ seqno; } ;
struct TYPE_6__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 TYPE_3__* __ipa_cmd (struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  qeth_mpc_finalize_cmd (struct qeth_card*,struct qeth_cmd_buffer*) ; 

__attribute__((used)) static void qeth_ipa_finalize_cmd(struct qeth_card *card,
				  struct qeth_cmd_buffer *iob)
{
	qeth_mpc_finalize_cmd(card, iob);

	/* override with IPA-specific values: */
	__ipa_cmd(iob)->hdr.seqno = card->seqno.ipa++;
}