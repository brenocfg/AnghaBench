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
typedef  enum spu_cipher_type { ____Placeholder_spu_cipher_type } spu_cipher_type ;
typedef  enum spu2_hash_type { ____Placeholder_spu2_hash_type } spu2_hash_type ;
typedef  enum spu2_hash_mode { ____Placeholder_spu2_hash_mode } spu2_hash_mode ;
typedef  enum hash_type { ____Placeholder_hash_type } hash_type ;
typedef  enum hash_mode { ____Placeholder_hash_mode } hash_mode ;
typedef  enum hash_alg { ____Placeholder_hash_alg } hash_alg ;

/* Variables and functions */
#define  CIPHER_TYPE_AES128 143 
#define  CIPHER_TYPE_AES192 142 
#define  CIPHER_TYPE_AES256 141 
 int EINVAL ; 
#define  HASH_ALG_AES 140 
#define  HASH_ALG_LAST 139 
#define  HASH_ALG_MD5 138 
#define  HASH_ALG_NONE 137 
#define  HASH_ALG_SHA1 136 
#define  HASH_ALG_SHA224 135 
#define  HASH_ALG_SHA256 134 
#define  HASH_ALG_SHA384 133 
#define  HASH_ALG_SHA3_224 132 
#define  HASH_ALG_SHA3_256 131 
#define  HASH_ALG_SHA3_384 130 
#define  HASH_ALG_SHA3_512 129 
#define  HASH_ALG_SHA512 128 
 int SPU2_HASH_TYPE_AES128 ; 
 int SPU2_HASH_TYPE_AES192 ; 
 int SPU2_HASH_TYPE_AES256 ; 
 int SPU2_HASH_TYPE_MD5 ; 
 int SPU2_HASH_TYPE_NONE ; 
 int SPU2_HASH_TYPE_SHA1 ; 
 int SPU2_HASH_TYPE_SHA224 ; 
 int SPU2_HASH_TYPE_SHA256 ; 
 int SPU2_HASH_TYPE_SHA384 ; 
 int SPU2_HASH_TYPE_SHA3_224 ; 
 int SPU2_HASH_TYPE_SHA3_256 ; 
 int SPU2_HASH_TYPE_SHA3_384 ; 
 int SPU2_HASH_TYPE_SHA3_512 ; 
 int SPU2_HASH_TYPE_SHA512 ; 
 int /*<<< orphan*/  flow_log (char*,int,...) ; 
 int spu2_hash_mode_xlate (int,int*) ; 

__attribute__((used)) static int
spu2_hash_xlate(enum hash_alg hash_alg, enum hash_mode hash_mode,
		enum hash_type hash_type, enum spu_cipher_type ciph_type,
		enum spu2_hash_type *spu2_type, enum spu2_hash_mode *spu2_mode)
{
	int err;

	err = spu2_hash_mode_xlate(hash_mode, spu2_mode);
	if (err) {
		flow_log("Invalid hash mode %d\n", hash_mode);
		return err;
	}

	switch (hash_alg) {
	case HASH_ALG_NONE:
		*spu2_type = SPU2_HASH_TYPE_NONE;
		break;
	case HASH_ALG_MD5:
		*spu2_type = SPU2_HASH_TYPE_MD5;
		break;
	case HASH_ALG_SHA1:
		*spu2_type = SPU2_HASH_TYPE_SHA1;
		break;
	case HASH_ALG_SHA224:
		*spu2_type = SPU2_HASH_TYPE_SHA224;
		break;
	case HASH_ALG_SHA256:
		*spu2_type = SPU2_HASH_TYPE_SHA256;
		break;
	case HASH_ALG_SHA384:
		*spu2_type = SPU2_HASH_TYPE_SHA384;
		break;
	case HASH_ALG_SHA512:
		*spu2_type = SPU2_HASH_TYPE_SHA512;
		break;
	case HASH_ALG_AES:
		switch (ciph_type) {
		case CIPHER_TYPE_AES128:
			*spu2_type = SPU2_HASH_TYPE_AES128;
			break;
		case CIPHER_TYPE_AES192:
			*spu2_type = SPU2_HASH_TYPE_AES192;
			break;
		case CIPHER_TYPE_AES256:
			*spu2_type = SPU2_HASH_TYPE_AES256;
			break;
		default:
			err = -EINVAL;
		}
		break;
	case HASH_ALG_SHA3_224:
		*spu2_type = SPU2_HASH_TYPE_SHA3_224;
		break;
	case HASH_ALG_SHA3_256:
		*spu2_type = SPU2_HASH_TYPE_SHA3_256;
		break;
	case HASH_ALG_SHA3_384:
		*spu2_type = SPU2_HASH_TYPE_SHA3_384;
		break;
	case HASH_ALG_SHA3_512:
		*spu2_type = SPU2_HASH_TYPE_SHA3_512;
		break;
	case HASH_ALG_LAST:
	default:
		err = -EINVAL;
		break;
	}

	if (err)
		flow_log("Invalid hash alg %d or type %d\n",
			 hash_alg, hash_type);
	return err;
}