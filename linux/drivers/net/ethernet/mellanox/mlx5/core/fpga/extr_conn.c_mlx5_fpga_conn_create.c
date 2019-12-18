#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mlx5_fpga_device {int /*<<< orphan*/  mdev; } ;
struct mlx5_fpga_conn_attr {int tx_size; int rx_size; int /*<<< orphan*/  cb_arg; scalar_t__ recv_cb; } ;
struct TYPE_5__ {int qpn; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  backlog; } ;
struct TYPE_6__ {int /*<<< orphan*/  sgid_index; TYPE_2__ mqp; TYPE_1__ sq; } ;
struct mlx5_fpga_conn {TYPE_3__ qp; int /*<<< orphan*/  fpga_qpn; struct mlx5_fpga_device* fdev; int /*<<< orphan*/  fpga_qpc; int /*<<< orphan*/  cb_arg; scalar_t__ recv_cb; } ;
typedef  enum mlx5_ifc_fpga_qp_type { ____Placeholder_mlx5_ifc_fpga_qp_type } mlx5_ifc_fpga_qp_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct mlx5_fpga_conn* ERR_PTR (int) ; 
 int ETH_P_8021Q ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int MLX5_FPGA_PKEY ; 
 int /*<<< orphan*/  MLX5_FPGA_PORT_NUM ; 
 int MLX5_FPGA_QPC_STATE_INIT ; 
 int MLX5_FPGA_QPC_ST_RC ; 
 int /*<<< orphan*/  MLX5_ROCE_L3_TYPE_IPV6 ; 
 int /*<<< orphan*/  MLX5_ROCE_VERSION_2 ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  addrconf_addr_eui48 (int*,int*) ; 
 int ether_type ; 
 int /*<<< orphan*/  fpga_qpc ; 
 int /*<<< orphan*/  kfree (struct mlx5_fpga_conn*) ; 
 struct mlx5_fpga_conn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_reserved_gid_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_reserved_gid_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_core_roce_gid_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_arm_cq (struct mlx5_fpga_conn*) ; 
 int mlx5_fpga_conn_connect (struct mlx5_fpga_conn*) ; 
 int mlx5_fpga_conn_create_cq (struct mlx5_fpga_conn*,int) ; 
 int mlx5_fpga_conn_create_qp (struct mlx5_fpga_conn*,int,int) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_destroy_cq (struct mlx5_fpga_conn*) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_destroy_qp (struct mlx5_fpga_conn*) ; 
 int mlx5_fpga_create_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fpga_dbg (struct mlx5_fpga_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_destroy_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_err (struct mlx5_fpga_device*,char*,int) ; 
 int mlx5_query_mac_address (int /*<<< orphan*/ ,int*) ; 
 int next_rcv_psn ; 
 int next_send_psn ; 
 int pkey ; 
 int* remote_mac_47_32 ; 
 int remote_qpn ; 
 int retry_count ; 
 int rnr_retry ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int st ; 
 int state ; 
 int vid ; 

struct mlx5_fpga_conn *mlx5_fpga_conn_create(struct mlx5_fpga_device *fdev,
					     struct mlx5_fpga_conn_attr *attr,
					     enum mlx5_ifc_fpga_qp_type qp_type)
{
	struct mlx5_fpga_conn *ret, *conn;
	u8 *remote_mac, *remote_ip;
	int err;

	if (!attr->recv_cb)
		return ERR_PTR(-EINVAL);

	conn = kzalloc(sizeof(*conn), GFP_KERNEL);
	if (!conn)
		return ERR_PTR(-ENOMEM);

	conn->fdev = fdev;
	INIT_LIST_HEAD(&conn->qp.sq.backlog);

	spin_lock_init(&conn->qp.sq.lock);

	conn->recv_cb = attr->recv_cb;
	conn->cb_arg = attr->cb_arg;

	remote_mac = MLX5_ADDR_OF(fpga_qpc, conn->fpga_qpc, remote_mac_47_32);
	err = mlx5_query_mac_address(fdev->mdev, remote_mac);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to query local MAC: %d\n", err);
		ret = ERR_PTR(err);
		goto err;
	}

	/* Build Modified EUI-64 IPv6 address from the MAC address */
	remote_ip = MLX5_ADDR_OF(fpga_qpc, conn->fpga_qpc, remote_ip);
	remote_ip[0] = 0xfe;
	remote_ip[1] = 0x80;
	addrconf_addr_eui48(&remote_ip[8], remote_mac);

	err = mlx5_core_reserved_gid_alloc(fdev->mdev, &conn->qp.sgid_index);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to allocate SGID: %d\n", err);
		ret = ERR_PTR(err);
		goto err;
	}

	err = mlx5_core_roce_gid_set(fdev->mdev, conn->qp.sgid_index,
				     MLX5_ROCE_VERSION_2,
				     MLX5_ROCE_L3_TYPE_IPV6,
				     remote_ip, remote_mac, true, 0,
				     MLX5_FPGA_PORT_NUM);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to set SGID: %d\n", err);
		ret = ERR_PTR(err);
		goto err_rsvd_gid;
	}
	mlx5_fpga_dbg(fdev, "Reserved SGID index %u\n", conn->qp.sgid_index);

	/* Allow for one cqe per rx/tx wqe, plus one cqe for the next wqe,
	 * created during processing of the cqe
	 */
	err = mlx5_fpga_conn_create_cq(conn,
				       (attr->tx_size + attr->rx_size) * 2);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to create CQ: %d\n", err);
		ret = ERR_PTR(err);
		goto err_gid;
	}

	mlx5_fpga_conn_arm_cq(conn);

	err = mlx5_fpga_conn_create_qp(conn, attr->tx_size, attr->rx_size);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to create QP: %d\n", err);
		ret = ERR_PTR(err);
		goto err_cq;
	}

	MLX5_SET(fpga_qpc, conn->fpga_qpc, state, MLX5_FPGA_QPC_STATE_INIT);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, qp_type, qp_type);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, st, MLX5_FPGA_QPC_ST_RC);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, ether_type, ETH_P_8021Q);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, vid, 0);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, next_rcv_psn, 1);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, next_send_psn, 0);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, pkey, MLX5_FPGA_PKEY);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, remote_qpn, conn->qp.mqp.qpn);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, rnr_retry, 7);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, retry_count, 7);

	err = mlx5_fpga_create_qp(fdev->mdev, &conn->fpga_qpc,
				  &conn->fpga_qpn);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to create FPGA RC QP: %d\n", err);
		ret = ERR_PTR(err);
		goto err_qp;
	}

	err = mlx5_fpga_conn_connect(conn);
	if (err) {
		ret = ERR_PTR(err);
		goto err_conn;
	}

	mlx5_fpga_dbg(fdev, "FPGA QPN is %u\n", conn->fpga_qpn);
	ret = conn;
	goto out;

err_conn:
	mlx5_fpga_destroy_qp(conn->fdev->mdev, conn->fpga_qpn);
err_qp:
	mlx5_fpga_conn_destroy_qp(conn);
err_cq:
	mlx5_fpga_conn_destroy_cq(conn);
err_gid:
	mlx5_core_roce_gid_set(fdev->mdev, conn->qp.sgid_index, 0, 0, NULL,
			       NULL, false, 0, MLX5_FPGA_PORT_NUM);
err_rsvd_gid:
	mlx5_core_reserved_gid_free(fdev->mdev, conn->qp.sgid_index);
err:
	kfree(conn);
out:
	return ret;
}