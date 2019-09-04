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
typedef  int /*<<< orphan*/  u_char ;
struct mtd_info {int dummy; } ;
struct kvec {size_t iov_len; void* iov_base; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int lpddr_writev (struct mtd_info*,struct kvec*,int,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int lpddr_write_buffers(struct mtd_info *mtd, loff_t to, size_t len,
				size_t *retlen, const u_char *buf)
{
	struct kvec vec;

	vec.iov_base = (void *) buf;
	vec.iov_len = len;

	return lpddr_writev(mtd, &vec, 1, to, retlen);
}