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
struct socket {int dummy; } ;
struct nvmet_tcp_queue {int idx; int /*<<< orphan*/  connect; int /*<<< orphan*/  nvme_sq; int /*<<< orphan*/  queue_list; int /*<<< orphan*/  io_work; int /*<<< orphan*/  cpu; int /*<<< orphan*/  resp_send_list; int /*<<< orphan*/  resp_list; int /*<<< orphan*/  free_list; int /*<<< orphan*/  state; int /*<<< orphan*/  state_lock; scalar_t__ nr_cmds; struct nvmet_tcp_port* port; struct socket* sock; int /*<<< orphan*/  release_work; } ;
struct nvmet_tcp_port {int /*<<< orphan*/  last_cpu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVMET_TCP_Q_CONNECTING ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_next_wrap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nvmet_tcp_queue*) ; 
 struct nvmet_tcp_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_prepare_receive_pdu (struct nvmet_tcp_queue*) ; 
 int /*<<< orphan*/  nvmet_sq_destroy (int /*<<< orphan*/ *) ; 
 int nvmet_sq_init (int /*<<< orphan*/ *) ; 
 int nvmet_tcp_alloc_cmd (struct nvmet_tcp_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_tcp_free_cmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_tcp_io_work ; 
 int /*<<< orphan*/  nvmet_tcp_queue_ida ; 
 int /*<<< orphan*/  nvmet_tcp_queue_list ; 
 int /*<<< orphan*/  nvmet_tcp_queue_mutex ; 
 int /*<<< orphan*/  nvmet_tcp_release_queue_work ; 
 int nvmet_tcp_set_queue_sock (struct nvmet_tcp_queue*) ; 
 int /*<<< orphan*/  nvmet_tcp_wq ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvmet_tcp_alloc_queue(struct nvmet_tcp_port *port,
		struct socket *newsock)
{
	struct nvmet_tcp_queue *queue;
	int ret;

	queue = kzalloc(sizeof(*queue), GFP_KERNEL);
	if (!queue)
		return -ENOMEM;

	INIT_WORK(&queue->release_work, nvmet_tcp_release_queue_work);
	INIT_WORK(&queue->io_work, nvmet_tcp_io_work);
	queue->sock = newsock;
	queue->port = port;
	queue->nr_cmds = 0;
	spin_lock_init(&queue->state_lock);
	queue->state = NVMET_TCP_Q_CONNECTING;
	INIT_LIST_HEAD(&queue->free_list);
	init_llist_head(&queue->resp_list);
	INIT_LIST_HEAD(&queue->resp_send_list);

	queue->idx = ida_simple_get(&nvmet_tcp_queue_ida, 0, 0, GFP_KERNEL);
	if (queue->idx < 0) {
		ret = queue->idx;
		goto out_free_queue;
	}

	ret = nvmet_tcp_alloc_cmd(queue, &queue->connect);
	if (ret)
		goto out_ida_remove;

	ret = nvmet_sq_init(&queue->nvme_sq);
	if (ret)
		goto out_free_connect;

	port->last_cpu = cpumask_next_wrap(port->last_cpu,
				cpu_online_mask, -1, false);
	queue->cpu = port->last_cpu;
	nvmet_prepare_receive_pdu(queue);

	mutex_lock(&nvmet_tcp_queue_mutex);
	list_add_tail(&queue->queue_list, &nvmet_tcp_queue_list);
	mutex_unlock(&nvmet_tcp_queue_mutex);

	ret = nvmet_tcp_set_queue_sock(queue);
	if (ret)
		goto out_destroy_sq;

	queue_work_on(queue->cpu, nvmet_tcp_wq, &queue->io_work);

	return 0;
out_destroy_sq:
	mutex_lock(&nvmet_tcp_queue_mutex);
	list_del_init(&queue->queue_list);
	mutex_unlock(&nvmet_tcp_queue_mutex);
	nvmet_sq_destroy(&queue->nvme_sq);
out_free_connect:
	nvmet_tcp_free_cmd(&queue->connect);
out_ida_remove:
	ida_simple_remove(&nvmet_tcp_queue_ida, queue->idx);
out_free_queue:
	kfree(queue);
	return ret;
}