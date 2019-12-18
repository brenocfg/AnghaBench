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
struct qeth_cmd_buffer {int /*<<< orphan*/  finalize; int /*<<< orphan*/  data; } ;
struct qeth_card {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_WRITE ; 
 int /*<<< orphan*/  QETH_TIMEOUT ; 
 int /*<<< orphan*/  __ccw_from_cmd (struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,unsigned int) ; 
 struct qeth_cmd_buffer* qeth_alloc_cmd (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_mpc_finalize_cmd ; 
 int /*<<< orphan*/  qeth_setup_ccw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct qeth_cmd_buffer *qeth_mpc_alloc_cmd(struct qeth_card *card,
						  void *data,
						  unsigned int data_length)
{
	struct qeth_cmd_buffer *iob;

	iob = qeth_alloc_cmd(&card->write, data_length, 1, QETH_TIMEOUT);
	if (!iob)
		return NULL;

	memcpy(iob->data, data, data_length);
	qeth_setup_ccw(__ccw_from_cmd(iob), CCW_CMD_WRITE, 0, data_length,
		       iob->data);
	iob->finalize = qeth_mpc_finalize_cmd;
	return iob;
}