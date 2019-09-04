#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct net_device {int dummy; } ;
struct neighbour {int nud_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  ha; TYPE_6__* tbl; int /*<<< orphan*/  primary_key; TYPE_4__* ops; int /*<<< orphan*/  dev; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct TYPE_11__ {int /*<<< orphan*/  dst_ip; int /*<<< orphan*/  family; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_9__ {TYPE_2__ ipv4; } ;
struct ip_tunnel_key {int tos; int ttl; int /*<<< orphan*/  tun_id; int /*<<< orphan*/  tp_dst; TYPE_3__ u; } ;
struct TYPE_7__ {struct ip_tunnel_key key; } ;
struct mlx5e_encap_entry {int tunnel_type; int encap_size; char* encap_header; struct net_device* out_dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  encap_id; int /*<<< orphan*/  h_dest; TYPE_5__ m_neigh; TYPE_1__ tun_info; } ;
struct iphdr {int dummy; } ;
struct flowi4 {int flowi4_tos; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  fl4_dport; int /*<<< orphan*/  flowi4_proto; } ;
struct TYPE_12__ {int /*<<< orphan*/  key_len; } ;
struct TYPE_10__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int MLX5_CAP_ESW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_ENCAP_ENTRY_VALID ; 
#define  MLX5_HEADER_TYPE_VXLAN 128 
 int NUD_VALID ; 
 int VXLAN_HLEN ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_vxlan_header_ipv4 (struct net_device*,char*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_encap_header_size ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int mlx5_encap_alloc (int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ *) ; 
 int mlx5e_rep_encap_entry_attach (int /*<<< orphan*/ ,struct mlx5e_encap_entry*) ; 
 int /*<<< orphan*/  mlx5e_rep_encap_entry_detach (int /*<<< orphan*/ ,struct mlx5e_encap_entry*) ; 
 int /*<<< orphan*/  mlx5e_rep_queue_neigh_stats_work (int /*<<< orphan*/ ) ; 
 int mlx5e_route_lookup_ipv4 (struct mlx5e_priv*,struct net_device*,struct net_device**,struct flowi4*,struct neighbour**,int*) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tunnel_id_to_key32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_create_encap_header_ipv4(struct mlx5e_priv *priv,
					  struct net_device *mirred_dev,
					  struct mlx5e_encap_entry *e)
{
	int max_encap_size = MLX5_CAP_ESW(priv->mdev, max_encap_header_size);
	int ipv4_encap_size = ETH_HLEN + sizeof(struct iphdr) + VXLAN_HLEN;
	struct ip_tunnel_key *tun_key = &e->tun_info.key;
	struct net_device *out_dev;
	struct neighbour *n = NULL;
	struct flowi4 fl4 = {};
	u8 nud_state, tos, ttl;
	char *encap_header;
	int err;

	if (max_encap_size < ipv4_encap_size) {
		mlx5_core_warn(priv->mdev, "encap size %d too big, max supported is %d\n",
			       ipv4_encap_size, max_encap_size);
		return -EOPNOTSUPP;
	}

	encap_header = kzalloc(ipv4_encap_size, GFP_KERNEL);
	if (!encap_header)
		return -ENOMEM;

	switch (e->tunnel_type) {
	case MLX5_HEADER_TYPE_VXLAN:
		fl4.flowi4_proto = IPPROTO_UDP;
		fl4.fl4_dport = tun_key->tp_dst;
		break;
	default:
		err = -EOPNOTSUPP;
		goto free_encap;
	}

	tos = tun_key->tos;
	ttl = tun_key->ttl;

	fl4.flowi4_tos = tun_key->tos;
	fl4.daddr = tun_key->u.ipv4.dst;
	fl4.saddr = tun_key->u.ipv4.src;

	err = mlx5e_route_lookup_ipv4(priv, mirred_dev, &out_dev,
				      &fl4, &n, &ttl);
	if (err)
		goto free_encap;

	/* used by mlx5e_detach_encap to lookup a neigh hash table
	 * entry in the neigh hash table when a user deletes a rule
	 */
	e->m_neigh.dev = n->dev;
	e->m_neigh.family = n->ops->family;
	memcpy(&e->m_neigh.dst_ip, n->primary_key, n->tbl->key_len);
	e->out_dev = out_dev;

	/* It's importent to add the neigh to the hash table before checking
	 * the neigh validity state. So if we'll get a notification, in case the
	 * neigh changes it's validity state, we would find the relevant neigh
	 * in the hash.
	 */
	err = mlx5e_rep_encap_entry_attach(netdev_priv(out_dev), e);
	if (err)
		goto free_encap;

	read_lock_bh(&n->lock);
	nud_state = n->nud_state;
	ether_addr_copy(e->h_dest, n->ha);
	read_unlock_bh(&n->lock);

	switch (e->tunnel_type) {
	case MLX5_HEADER_TYPE_VXLAN:
		gen_vxlan_header_ipv4(out_dev, encap_header,
				      ipv4_encap_size, e->h_dest, tos, ttl,
				      fl4.daddr,
				      fl4.saddr, tun_key->tp_dst,
				      tunnel_id_to_key32(tun_key->tun_id));
		break;
	default:
		err = -EOPNOTSUPP;
		goto destroy_neigh_entry;
	}
	e->encap_size = ipv4_encap_size;
	e->encap_header = encap_header;

	if (!(nud_state & NUD_VALID)) {
		neigh_event_send(n, NULL);
		err = -EAGAIN;
		goto out;
	}

	err = mlx5_encap_alloc(priv->mdev, e->tunnel_type,
			       ipv4_encap_size, encap_header, &e->encap_id);
	if (err)
		goto destroy_neigh_entry;

	e->flags |= MLX5_ENCAP_ENTRY_VALID;
	mlx5e_rep_queue_neigh_stats_work(netdev_priv(out_dev));
	neigh_release(n);
	return err;

destroy_neigh_entry:
	mlx5e_rep_encap_entry_detach(netdev_priv(e->out_dev), e);
free_encap:
	kfree(encap_header);
out:
	if (n)
		neigh_release(n);
	return err;
}