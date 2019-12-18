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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qeth_qdio_out_buffer {TYPE_2__* buffer; } ;
struct qeth_card {int dummy; } ;
struct TYPE_4__ {TYPE_1__* element; } ;
struct TYPE_3__ {int sflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_check_qdio_errors (struct qeth_card*,TYPE_2__*,unsigned int,char*) ; 

__attribute__((used)) static void qeth_handle_send_error(struct qeth_card *card,
		struct qeth_qdio_out_buffer *buffer, unsigned int qdio_err)
{
	int sbalf15 = buffer->buffer->element[15].sflags;

	QETH_CARD_TEXT(card, 6, "hdsnderr");
	qeth_check_qdio_errors(card, buffer->buffer, qdio_err, "qouterr");

	if (!qdio_err)
		return;

	if ((sbalf15 >= 15) && (sbalf15 <= 31))
		return;

	QETH_CARD_TEXT(card, 1, "lnkfail");
	QETH_CARD_TEXT_(card, 1, "%04x %02x",
		       (u16)qdio_err, (u8)sbalf15);
}