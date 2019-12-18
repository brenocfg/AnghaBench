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
typedef  int /*<<< orphan*/  u8 ;
struct qstr {scalar_t__ len; scalar_t__ name; } ;
struct inode {int dummy; } ;
struct file_id_t {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ffsLookupFile (struct inode*,int /*<<< orphan*/ *,struct file_id_t*) ; 

__attribute__((used)) static int exfat_find(struct inode *dir, struct qstr *qname,
		      struct file_id_t *fid)
{
	int err;

	if (qname->len == 0)
		return -ENOENT;

	err = ffsLookupFile(dir, (u8 *)qname->name, fid);
	if (err)
		return -ENOENT;

	return 0;
}