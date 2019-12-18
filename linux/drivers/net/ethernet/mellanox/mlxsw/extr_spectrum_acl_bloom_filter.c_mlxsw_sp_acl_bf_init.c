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
struct mlxsw_sp_acl_bf {unsigned int bank_size; int /*<<< orphan*/  lock; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_MAX_BF_LOG ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct mlxsw_sp_acl_bf* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_acl_bf* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcnt ; 
 int /*<<< orphan*/  struct_size (struct mlxsw_sp_acl_bf*,int /*<<< orphan*/ ,unsigned int) ; 

struct mlxsw_sp_acl_bf *
mlxsw_sp_acl_bf_init(struct mlxsw_sp *mlxsw_sp, unsigned int num_erp_banks)
{
	struct mlxsw_sp_acl_bf *bf;
	unsigned int bf_bank_size;

	if (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_MAX_BF_LOG))
		return ERR_PTR(-EIO);

	/* Bloom filter size per erp_table_bank
	 * is 2^ACL_MAX_BF_LOG
	 */
	bf_bank_size = 1 << MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_MAX_BF_LOG);
	bf = kzalloc(struct_size(bf, refcnt, bf_bank_size * num_erp_banks),
		     GFP_KERNEL);
	if (!bf)
		return ERR_PTR(-ENOMEM);

	bf->bank_size = bf_bank_size;
	mutex_init(&bf->lock);

	return bf;
}