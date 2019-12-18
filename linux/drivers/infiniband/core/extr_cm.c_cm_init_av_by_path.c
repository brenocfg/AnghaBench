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
struct sa_path_rec {scalar_t__ packet_life_time; int /*<<< orphan*/  pkey; } ;
struct rdma_ah_attr {int dummy; } ;
struct ib_gid_attr {int dummy; } ;
struct cm_port {int /*<<< orphan*/  port_num; struct cm_device* cm_dev; } ;
struct cm_id_private {int dummy; } ;
struct cm_device {int /*<<< orphan*/  ib_device; } ;
struct cm_av {int /*<<< orphan*/  ah_attr; scalar_t__ timeout; struct cm_port* port; int /*<<< orphan*/  pkey_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int add_cm_id_to_port_list (struct cm_id_private*,struct cm_av*,struct cm_port*) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct cm_port* get_cm_port_from_path (struct sa_path_rec*,struct ib_gid_attr const*) ; 
 int ib_find_cached_pkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ib_init_ah_attr_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sa_path_rec*,struct rdma_ah_attr*,struct ib_gid_attr const*) ; 
 int /*<<< orphan*/  rdma_destroy_ah_attr (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_move_ah_attr (int /*<<< orphan*/ *,struct rdma_ah_attr*) ; 

__attribute__((used)) static int cm_init_av_by_path(struct sa_path_rec *path,
			      const struct ib_gid_attr *sgid_attr,
			      struct cm_av *av,
			      struct cm_id_private *cm_id_priv)
{
	struct rdma_ah_attr new_ah_attr;
	struct cm_device *cm_dev;
	struct cm_port *port;
	int ret;

	port = get_cm_port_from_path(path, sgid_attr);
	if (!port)
		return -EINVAL;
	cm_dev = port->cm_dev;

	ret = ib_find_cached_pkey(cm_dev->ib_device, port->port_num,
				  be16_to_cpu(path->pkey), &av->pkey_index);
	if (ret)
		return ret;

	av->port = port;

	/*
	 * av->ah_attr might be initialized based on wc or during
	 * request processing time which might have reference to sgid_attr.
	 * So initialize a new ah_attr on stack.
	 * If initialization fails, old ah_attr is used for sending any
	 * responses. If initialization is successful, than new ah_attr
	 * is used by overwriting the old one. So that right ah_attr
	 * can be used to return an error response.
	 */
	ret = ib_init_ah_attr_from_path(cm_dev->ib_device, port->port_num, path,
					&new_ah_attr, sgid_attr);
	if (ret)
		return ret;

	av->timeout = path->packet_life_time + 1;

	ret = add_cm_id_to_port_list(cm_id_priv, av, port);
	if (ret) {
		rdma_destroy_ah_attr(&new_ah_attr);
		return ret;
	}
	rdma_move_ah_attr(&av->ah_attr, &new_ah_attr);
	return 0;
}