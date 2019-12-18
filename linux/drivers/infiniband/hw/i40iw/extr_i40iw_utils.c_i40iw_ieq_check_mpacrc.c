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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct shash_desc {int dummy; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int I40IW_ERR_MPA_CRC ; 
 int /*<<< orphan*/  crypto_shash_final (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_shash_init (struct shash_desc*) ; 
 int crypto_shash_update (struct shash_desc*,void*,scalar_t__) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 

enum i40iw_status_code i40iw_ieq_check_mpacrc(struct shash_desc *desc,
					      void *addr,
					      u32 length,
					      u32 value)
{
	u32 crc = 0;
	int ret;
	enum i40iw_status_code ret_code = 0;

	crypto_shash_init(desc);
	ret = crypto_shash_update(desc, addr, length);
	if (!ret)
		crypto_shash_final(desc, (u8 *)&crc);
	if (crc != value) {
		i40iw_pr_err("mpa crc check fail\n");
		ret_code = I40IW_ERR_MPA_CRC;
	}
	return ret_code;
}