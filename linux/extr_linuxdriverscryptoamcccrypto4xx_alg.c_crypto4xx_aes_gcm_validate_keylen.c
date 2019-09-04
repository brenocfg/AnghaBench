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

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int crypto4xx_aes_gcm_validate_keylen(unsigned int keylen)
{
	switch (keylen) {
	case 16:
	case 24:
	case 32:
		return 0;
	default:
		return -EINVAL;
	}
}