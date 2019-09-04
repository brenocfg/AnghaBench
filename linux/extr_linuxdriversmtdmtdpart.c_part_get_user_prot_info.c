#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct otp_info {int dummy; } ;
struct mtd_part {TYPE_1__* parent; } ;
struct mtd_info {int dummy; } ;
struct TYPE_2__ {int (* _get_user_prot_info ) (TYPE_1__*,size_t,size_t*,struct otp_info*) ;} ;

/* Variables and functions */
 struct mtd_part* mtd_to_part (struct mtd_info*) ; 
 int stub1 (TYPE_1__*,size_t,size_t*,struct otp_info*) ; 

__attribute__((used)) static int part_get_user_prot_info(struct mtd_info *mtd, size_t len,
				   size_t *retlen, struct otp_info *buf)
{
	struct mtd_part *part = mtd_to_part(mtd);
	return part->parent->_get_user_prot_info(part->parent, len, retlen,
						 buf);
}