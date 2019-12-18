#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct net_device {int dummy; } ;
struct neighbour {int nud_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  ha; TYPE_7__* tbl; int /*<<< orphan*/  primary_key; TYPE_5__* ops; int /*<<< orphan*/  dev; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct TYPE_13__ {int /*<<< orphan*/  dst_ip; int /*<<< orphan*/  family; int /*<<< orphan*/  dev; } ;
struct mlx5e_encap_entry {int encap_size; char* encap_header; struct net_device* out_dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  pkt_reformat; int /*<<< orphan*/  reformat_type; int /*<<< orphan*/  h_dest; struct net_device* route_dev; TYPE_6__ m_neigh; TYPE_4__* tunnel; TYPE_1__* tun_info; } ;
struct iphdr {int version; int ihl; int ttl; int /*<<< orphan*/  protocol; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  tos; } ;
struct TYPE_9__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_10__ {TYPE_2__ ipv4; } ;
struct ip_tunnel_key {int ttl; int /*<<< orphan*/  tos; TYPE_3__ u; } ;
struct flowi4 {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi4_tos; } ;
struct TYPE_14__ {int /*<<< orphan*/  key_len; } ;
struct TYPE_12__ {int /*<<< orphan*/  family; } ;
struct TYPE_11__ {int (* calc_hlen ) (struct mlx5e_encap_entry*) ;} ;
struct TYPE_8__ {struct ip_tunnel_key key; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MLX5_CAP_ESW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_ENCAP_ENTRY_VALID ; 
 int /*<<< orphan*/  MLX5_FLOW_NAMESPACE_FDB ; 
 int NUD_VALID ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int VLAN_ETH_HLEN ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_eth_tnl_hdr (char*,struct net_device*,struct mlx5e_encap_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_encap_header_size ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mlx5_packet_reformat_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int mlx5e_gen_ip_tunnel_header (char*,int /*<<< orphan*/ *,struct mlx5e_encap_entry*) ; 
 int mlx5e_rep_encap_entry_attach (int /*<<< orphan*/ ,struct mlx5e_encap_entry*) ; 
 int /*<<< orphan*/  mlx5e_rep_encap_entry_detach (int /*<<< orphan*/ ,struct mlx5e_encap_entry*) ; 
 int /*<<< orphan*/  mlx5e_rep_queue_neigh_stats_work (int /*<<< orphan*/ ) ; 
 int mlx5e_route_lookup_ipv4 (struct mlx5e_priv*,struct net_device*,struct net_device**,struct net_device**,struct flowi4*,struct neighbour**,int*) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct mlx5e_encap_entry*) ; 

int mlx5e_tc_tun_create_header_ipv4(struct mlx5e_priv *priv,
				    struct net_device *mirred_dev,
				    struct mlx5e_encap_entry *e)
{
	int max_encap_size = MLX5_CAP_ESW(priv->mdev, max_encap_header_size);
	const struct ip_tunnel_key *tun_key = &e->tun_info->key;
	struct net_device *out_dev, *route_dev;
	struct neighbour *n = NULL;
	struct flowi4 fl4 = {};
	int ipv4_encap_size;
	char *encap_header;
	u8 nud_state, ttl;
	struct iphdr *ip;
	int err;

	/* add the IP fields */
	fl4.flowi4_tos = tun_key->tos;
	fl4.daddr = tun_key->u.ipv4.dst;
	fl4.saddr = tun_key->u.ipv4.src;
	ttl = tun_key->ttl;

	err = mlx5e_route_lookup_ipv4(priv, mirred_dev, &out_dev, &route_dev,
				      &fl4, &n, &ttl);
	if (err)
		return err;

	ipv4_encap_size =
		(is_vlan_dev(route_dev) ? VLAN_ETH_HLEN : ETH_HLEN) +
		sizeof(struct iphdr) +
		e->tunnel->calc_hlen(e);

	if (max_encap_size < ipv4_encap_size) {
		mlx5_core_warn(priv->mdev, "encap size %d too big, max supported is %d\n",
			       ipv4_encap_size, max_encap_size);
		return -EOPNOTSUPP;
	}

	encap_header = kzalloc(ipv4_encap_size, GFP_KERNEL);
	if (!encap_header)
		return -ENOMEM;

	/* used by mlx5e_detach_encap to lookup a neigh hash table
	 * entry in the neigh hash table when a user deletes a rule
	 */
	e->m_neigh.dev = n->dev;
	e->m_neigh.family = n->ops->family;
	memcpy(&e->m_neigh.dst_ip, n->primary_key, n->tbl->key_len);
	e->out_dev = out_dev;
	e->route_dev = route_dev;

	/* It's important to add the neigh to the hash table before checking
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

	/* add ethernet header */
	ip = (struct iphdr *)gen_eth_tnl_hdr(encap_header, route_dev, e,
					     ETH_P_IP);

	/* add ip header */
	ip->tos = tun_key->tos;
	ip->version = 0x4;
	ip->ihl = 0x5;
	ip->ttl = ttl;
	ip->daddr = fl4.daddr;
	ip->saddr = fl4.saddr;

	/* add tunneling protocol header */
	err = mlx5e_gen_ip_tunnel_header((char *)ip + sizeof(struct iphdr),
					 &ip->protocol, e);
	if (err)
		goto destroy_neigh_entry;

	e->encap_size = ipv4_encap_size;
	e->encap_header = encap_header;

	if (!(nud_state & NUD_VALID)) {
		neigh_event_send(n, NULL);
		/* the encap entry will be made valid on neigh update event
		 * and not used before that.
		 */
		goto out;
	}
	e->pkt_reformat = mlx5_packet_reformat_alloc(priv->mdev,
						     e->reformat_type,
						     ipv4_encap_size, encap_header,
						     MLX5_FLOW_NAMESPACE_FDB);
	if (IS_ERR(e->pkt_reformat)) {
		err = PTR_ERR(e->pkt_reformat);
		goto destroy_neigh_entry;
	}

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