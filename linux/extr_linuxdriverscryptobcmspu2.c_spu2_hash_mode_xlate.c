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
typedef  enum spu2_hash_mode { ____Placeholder_spu2_hash_mode } spu2_hash_mode ;
typedef  enum hash_mode { ____Placeholder_hash_mode } hash_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  HASH_MODE_CCM 132 
#define  HASH_MODE_CMAC 131 
#define  HASH_MODE_GCM 130 
#define  HASH_MODE_HMAC 129 
#define  HASH_MODE_XCBC 128 
 int SPU2_HASH_MODE_CCM ; 
 int SPU2_HASH_MODE_CMAC ; 
 int SPU2_HASH_MODE_GCM ; 
 int SPU2_HASH_MODE_HMAC ; 
 int SPU2_HASH_MODE_XCBC_MAC ; 

__attribute__((used)) static int spu2_hash_mode_xlate(enum hash_mode hash_mode,
				enum spu2_hash_mode *spu2_mode)
{
	switch (hash_mode) {
	case HASH_MODE_XCBC:
		*spu2_mode = SPU2_HASH_MODE_XCBC_MAC;
		break;
	case HASH_MODE_CMAC:
		*spu2_mode = SPU2_HASH_MODE_CMAC;
		break;
	case HASH_MODE_HMAC:
		*spu2_mode = SPU2_HASH_MODE_HMAC;
		break;
	case HASH_MODE_CCM:
		*spu2_mode = SPU2_HASH_MODE_CCM;
		break;
	case HASH_MODE_GCM:
		*spu2_mode = SPU2_HASH_MODE_GCM;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}