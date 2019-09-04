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

/* Variables and functions */
 int /*<<< orphan*/  mpc5121_nfc_buf_copy (struct mtd_info*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void mpc5121_nfc_write_buf(struct mtd_info *mtd,
						const u_char *buf, int len)
{
	mpc5121_nfc_buf_copy(mtd, (u_char *)buf, len, 1);
}