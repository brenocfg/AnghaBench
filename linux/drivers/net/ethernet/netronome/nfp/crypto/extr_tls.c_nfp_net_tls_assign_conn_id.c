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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct nfp_net {int /*<<< orphan*/  ktls_conn_id_gen; } ;
struct nfp_crypto_req_add_front {scalar_t__ l3_addrs; scalar_t__ key_len; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 scalar_t__ NFP_NET_TLS_NON_ADDR_KEY_LEN ; 
 int /*<<< orphan*/  atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
nfp_net_tls_assign_conn_id(struct nfp_net *nn,
			   struct nfp_crypto_req_add_front *front)
{
	u32 len;
	u64 id;

	id = atomic64_inc_return(&nn->ktls_conn_id_gen);
	len = front->key_len - NFP_NET_TLS_NON_ADDR_KEY_LEN;

	memcpy(front->l3_addrs, &id, sizeof(id));
	memset(front->l3_addrs + sizeof(id), 0, len - sizeof(id));
}