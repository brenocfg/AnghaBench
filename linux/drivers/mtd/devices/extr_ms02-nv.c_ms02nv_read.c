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
struct mtd_info {struct ms02nv_private* priv; } ;
struct ms02nv_private {scalar_t__ uaddr; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,size_t) ; 

__attribute__((used)) static int ms02nv_read(struct mtd_info *mtd, loff_t from,
			size_t len, size_t *retlen, u_char *buf)
{
	struct ms02nv_private *mp = mtd->priv;

	memcpy(buf, mp->uaddr + from, len);
	*retlen = len;
	return 0;
}