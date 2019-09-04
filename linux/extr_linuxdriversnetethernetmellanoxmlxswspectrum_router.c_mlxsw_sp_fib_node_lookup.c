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
struct mlxsw_sp_fib_node {int dummy; } ;
struct mlxsw_sp_fib_key {unsigned char prefix_len; int /*<<< orphan*/  addr; } ;
struct mlxsw_sp_fib {int /*<<< orphan*/  ht; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  memset (struct mlxsw_sp_fib_key*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_ht_params ; 
 struct mlxsw_sp_fib_node* rhashtable_lookup_fast (int /*<<< orphan*/ *,struct mlxsw_sp_fib_key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_fib_node *
mlxsw_sp_fib_node_lookup(struct mlxsw_sp_fib *fib, const void *addr,
			 size_t addr_len, unsigned char prefix_len)
{
	struct mlxsw_sp_fib_key key;

	memset(&key, 0, sizeof(key));
	memcpy(key.addr, addr, addr_len);
	key.prefix_len = prefix_len;
	return rhashtable_lookup_fast(&fib->ht, &key, mlxsw_sp_fib_ht_params);
}