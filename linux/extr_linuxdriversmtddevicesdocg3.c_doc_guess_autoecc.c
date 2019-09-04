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
struct mtd_oob_ops {int mode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MTD_OPS_AUTO_OOB 130 
#define  MTD_OPS_PLACE_OOB 129 
#define  MTD_OPS_RAW 128 

__attribute__((used)) static int doc_guess_autoecc(struct mtd_oob_ops *ops)
{
	int autoecc;

	switch (ops->mode) {
	case MTD_OPS_PLACE_OOB:
	case MTD_OPS_AUTO_OOB:
		autoecc = 1;
		break;
	case MTD_OPS_RAW:
		autoecc = 0;
		break;
	default:
		autoecc = -EINVAL;
	}
	return autoecc;
}