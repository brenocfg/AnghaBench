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
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qeth_notify_cmd (struct qeth_cmd_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_put_cmd (struct qeth_cmd_buffer*) ; 

__attribute__((used)) static void qeth_osn_assist_cb(struct qeth_card *card,
			       struct qeth_cmd_buffer *iob,
			       unsigned int data_length)
{
	qeth_notify_cmd(iob, 0);
	qeth_put_cmd(iob);
}