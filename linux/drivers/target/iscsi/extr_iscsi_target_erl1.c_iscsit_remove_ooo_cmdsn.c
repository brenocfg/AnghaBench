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
struct iscsi_session {int dummy; } ;
struct iscsi_ooo_cmdsn {int /*<<< orphan*/  ooo_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct iscsi_ooo_cmdsn*) ; 
 int /*<<< orphan*/  lio_ooo_cache ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void iscsit_remove_ooo_cmdsn(
	struct iscsi_session *sess,
	struct iscsi_ooo_cmdsn *ooo_cmdsn)
{
	list_del(&ooo_cmdsn->ooo_list);
	kmem_cache_free(lio_ooo_cache, ooo_cmdsn);
}