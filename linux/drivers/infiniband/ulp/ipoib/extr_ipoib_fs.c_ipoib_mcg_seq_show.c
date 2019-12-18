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
typedef  union ib_gid {int dummy; } ib_gid ;
struct seq_file {int dummy; } ;
struct ipoib_mcast_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  format_gid (union ib_gid*,char*) ; 
 int /*<<< orphan*/  ipoib_mcast_iter_read (struct ipoib_mcast_iter*,union ib_gid*,unsigned long*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,unsigned long,unsigned int,char*,char*) ; 

__attribute__((used)) static int ipoib_mcg_seq_show(struct seq_file *file, void *iter_ptr)
{
	struct ipoib_mcast_iter *iter = iter_ptr;
	char gid_buf[sizeof "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"];
	union ib_gid mgid;
	unsigned long created;
	unsigned int queuelen, complete, send_only;

	if (!iter)
		return 0;

	ipoib_mcast_iter_read(iter, &mgid, &created, &queuelen,
			      &complete, &send_only);

	format_gid(&mgid, gid_buf);

	seq_printf(file,
		   "GID: %s\n"
		   "  created: %10ld\n"
		   "  queuelen: %9d\n"
		   "  complete: %9s\n"
		   "  send_only: %8s\n"
		   "\n",
		   gid_buf, created, queuelen,
		   complete ? "yes" : "no",
		   send_only ? "yes" : "no");

	return 0;
}