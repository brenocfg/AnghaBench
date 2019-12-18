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
struct docg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOC_CMD_RESET ; 
 int /*<<< orphan*/  DOC_FLASHCONTROL ; 
 int /*<<< orphan*/  DOC_SEQ_RESET ; 
 int /*<<< orphan*/  doc_dbg (char*,char*) ; 
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_flash_command (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_flash_sequence (struct docg3*,int /*<<< orphan*/ ) ; 
 int doc_wait_ready (struct docg3*) ; 
 int /*<<< orphan*/  doc_writeb (struct docg3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int doc_reset_seq(struct docg3 *docg3)
{
	int ret;

	doc_writeb(docg3, 0x10, DOC_FLASHCONTROL);
	doc_flash_sequence(docg3, DOC_SEQ_RESET);
	doc_flash_command(docg3, DOC_CMD_RESET);
	doc_delay(docg3, 2);
	ret = doc_wait_ready(docg3);

	doc_dbg("doc_reset_seq() -> isReady=%s\n", ret ? "false" : "true");
	return ret;
}