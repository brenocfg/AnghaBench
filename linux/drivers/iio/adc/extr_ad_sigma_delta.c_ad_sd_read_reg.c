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
struct ad_sigma_delta {int* data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ad_sd_read_reg_raw (struct ad_sigma_delta*,unsigned int,unsigned int,int*) ; 
 unsigned int get_unaligned_be16 (int*) ; 
 unsigned int get_unaligned_be32 (int*) ; 

int ad_sd_read_reg(struct ad_sigma_delta *sigma_delta,
	unsigned int reg, unsigned int size, unsigned int *val)
{
	int ret;

	ret = ad_sd_read_reg_raw(sigma_delta, reg, size, sigma_delta->data);
	if (ret < 0)
		goto out;

	switch (size) {
	case 4:
		*val = get_unaligned_be32(sigma_delta->data);
		break;
	case 3:
		*val = (sigma_delta->data[0] << 16) |
			(sigma_delta->data[1] << 8) |
			sigma_delta->data[2];
		break;
	case 2:
		*val = get_unaligned_be16(sigma_delta->data);
		break;
	case 1:
		*val = sigma_delta->data[0];
		break;
	default:
		ret = -EINVAL;
		break;
	}

out:
	return ret;
}