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
struct qeth_card {int dummy; } ;
struct qdio_buffer {TYPE_1__* element; } ;
struct TYPE_2__ {unsigned int sflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_STAT_INC (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char const*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  rx_dropped ; 

__attribute__((used)) static int qeth_check_qdio_errors(struct qeth_card *card,
				  struct qdio_buffer *buf,
				  unsigned int qdio_error,
				  const char *dbftext)
{
	if (qdio_error) {
		QETH_CARD_TEXT(card, 2, dbftext);
		QETH_CARD_TEXT_(card, 2, " F15=%02X",
			       buf->element[15].sflags);
		QETH_CARD_TEXT_(card, 2, " F14=%02X",
			       buf->element[14].sflags);
		QETH_CARD_TEXT_(card, 2, " qerr=%X", qdio_error);
		if ((buf->element[15].sflags) == 0x12) {
			QETH_CARD_STAT_INC(card, rx_dropped);
			return 0;
		} else
			return 1;
	}
	return 0;
}