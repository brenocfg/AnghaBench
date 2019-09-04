#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct docg3 {size_t reliable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOC_CMD_FAST_MODE ; 
 int /*<<< orphan*/  DOC_CMD_RELIABLE_MODE ; 
 int /*<<< orphan*/  DOC_SEQ_SET_FASTMODE ; 
 int /*<<< orphan*/  DOC_SEQ_SET_RELIABLEMODE ; 
 int /*<<< orphan*/  doc_dbg (char*,char*) ; 
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_err (char*) ; 
 int /*<<< orphan*/  doc_flash_command (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_flash_sequence (struct docg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void doc_set_reliable_mode(struct docg3 *docg3)
{
	static char *strmode[] = { "normal", "fast", "reliable", "invalid" };

	doc_dbg("doc_set_reliable_mode(%s)\n", strmode[docg3->reliable]);
	switch (docg3->reliable) {
	case 0:
		break;
	case 1:
		doc_flash_sequence(docg3, DOC_SEQ_SET_FASTMODE);
		doc_flash_command(docg3, DOC_CMD_FAST_MODE);
		break;
	case 2:
		doc_flash_sequence(docg3, DOC_SEQ_SET_RELIABLEMODE);
		doc_flash_command(docg3, DOC_CMD_FAST_MODE);
		doc_flash_command(docg3, DOC_CMD_RELIABLE_MODE);
		break;
	default:
		doc_err("doc_set_reliable_mode(): invalid mode\n");
		break;
	}
	doc_delay(docg3, 2);
}