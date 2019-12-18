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
struct iscsi_cls_session {int /*<<< orphan*/  dd_data; } ;

/* Variables and functions */
 int CXGBI_DBG_ISCSI ; 
 int /*<<< orphan*/  iscsi_session_teardown (struct iscsi_cls_session*) ; 
 int /*<<< orphan*/  iscsi_tcp_r2tpool_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct iscsi_cls_session*) ; 

void cxgbi_destroy_session(struct iscsi_cls_session *cls_session)
{
	log_debug(1 << CXGBI_DBG_ISCSI,
		"cls sess 0x%p.\n", cls_session);

	iscsi_tcp_r2tpool_free(cls_session->dd_data);
	iscsi_session_teardown(cls_session);
}