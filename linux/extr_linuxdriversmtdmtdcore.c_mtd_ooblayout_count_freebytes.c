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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int mtd_ooblayout_count_bytes (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_ooblayout_free ; 

int mtd_ooblayout_count_freebytes(struct mtd_info *mtd)
{
	return mtd_ooblayout_count_bytes(mtd, mtd_ooblayout_free);
}