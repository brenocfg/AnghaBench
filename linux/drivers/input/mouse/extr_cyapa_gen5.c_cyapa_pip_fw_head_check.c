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
struct cyapa_tsg_bin_image_head {int head_size; int family_id; int silicon_id_hi; } ;
struct cyapa {int gen; int platform_ver; } ;

/* Variables and functions */
#define  CYAPA_GEN5 129 
#define  CYAPA_GEN6 128 
 int EINVAL ; 

__attribute__((used)) static int cyapa_pip_fw_head_check(struct cyapa *cyapa,
		struct cyapa_tsg_bin_image_head *image_head)
{
	if (image_head->head_size != 0x0C && image_head->head_size != 0x12)
		return -EINVAL;

	switch (cyapa->gen) {
	case CYAPA_GEN6:
		if (image_head->family_id != 0x9B ||
		    image_head->silicon_id_hi != 0x0B)
			return -EINVAL;
		break;
	case CYAPA_GEN5:
		/* Gen5 without proximity support. */
		if (cyapa->platform_ver < 2) {
			if (image_head->head_size == 0x0C)
				break;
			return -EINVAL;
		}

		if (image_head->family_id != 0x91 ||
		    image_head->silicon_id_hi != 0x02)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}