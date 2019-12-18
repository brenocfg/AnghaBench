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
struct uverbs_attr_bundle {int dummy; } ;
struct devx_umem_reg_cmd {int inlen; int /*<<< orphan*/  in; } ;
struct devx_umem {int ncont; } ;

/* Variables and functions */
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_umem_in ; 
 int /*<<< orphan*/  mtt ; 
 int /*<<< orphan*/  uverbs_zalloc (struct uverbs_attr_bundle*,int) ; 

__attribute__((used)) static int devx_umem_reg_cmd_alloc(struct uverbs_attr_bundle *attrs,
				   struct devx_umem *obj,
				   struct devx_umem_reg_cmd *cmd)
{
	cmd->inlen = MLX5_ST_SZ_BYTES(create_umem_in) +
		    (MLX5_ST_SZ_BYTES(mtt) * obj->ncont);
	cmd->in = uverbs_zalloc(attrs, cmd->inlen);
	return PTR_ERR_OR_ZERO(cmd->in);
}