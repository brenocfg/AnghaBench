#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcp_sock {int rcv_nxt; int copied_seq; int write_seq; int snd_una; } ;
struct seq_file {struct drbd_resource* private; } ;
struct drbd_resource {int dummy; } ;
struct TYPE_4__ {TYPE_1__* socket; } ;
struct drbd_connection {int /*<<< orphan*/  kref; TYPE_2__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int ESTALE ; 
 int /*<<< orphan*/  drbd_destroy_connection ; 
 struct drbd_connection* first_connection (struct drbd_resource*) ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  seq_print_resource_pending_bitmap_io (struct seq_file*,struct drbd_resource*,unsigned long) ; 
 int /*<<< orphan*/  seq_print_resource_pending_meta_io (struct seq_file*,struct drbd_resource*,unsigned long) ; 
 int /*<<< orphan*/  seq_print_resource_pending_peer_requests (struct seq_file*,struct drbd_resource*,unsigned long) ; 
 int /*<<< orphan*/  seq_print_resource_transfer_log_summary (struct seq_file*,struct drbd_resource*,struct drbd_connection*,unsigned long) ; 
 int /*<<< orphan*/  seq_print_waiting_for_AL (struct seq_file*,struct drbd_resource*,unsigned long) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 struct tcp_sock* tcp_sk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int in_flight_summary_show(struct seq_file *m, void *pos)
{
	struct drbd_resource *resource = m->private;
	struct drbd_connection *connection;
	unsigned long jif = jiffies;

	connection = first_connection(resource);
	/* This does not happen, actually.
	 * But be robust and prepare for future code changes. */
	if (!connection || !kref_get_unless_zero(&connection->kref))
		return -ESTALE;

	/* BUMP me if you change the file format/content/presentation */
	seq_printf(m, "v: %u\n\n", 0);

	seq_puts(m, "oldest bitmap IO\n");
	seq_print_resource_pending_bitmap_io(m, resource, jif);
	seq_putc(m, '\n');

	seq_puts(m, "meta data IO\n");
	seq_print_resource_pending_meta_io(m, resource, jif);
	seq_putc(m, '\n');

	seq_puts(m, "socket buffer stats\n");
	/* for each connection ... once we have more than one */
	rcu_read_lock();
	if (connection->data.socket) {
		/* open coded SIOCINQ, the "relevant" part */
		struct tcp_sock *tp = tcp_sk(connection->data.socket->sk);
		int answ = tp->rcv_nxt - tp->copied_seq;
		seq_printf(m, "unread receive buffer: %u Byte\n", answ);
		/* open coded SIOCOUTQ, the "relevant" part */
		answ = tp->write_seq - tp->snd_una;
		seq_printf(m, "unacked send buffer: %u Byte\n", answ);
	}
	rcu_read_unlock();
	seq_putc(m, '\n');

	seq_puts(m, "oldest peer requests\n");
	seq_print_resource_pending_peer_requests(m, resource, jif);
	seq_putc(m, '\n');

	seq_puts(m, "application requests waiting for activity log\n");
	seq_print_waiting_for_AL(m, resource, jif);
	seq_putc(m, '\n');

	seq_puts(m, "oldest application requests\n");
	seq_print_resource_transfer_log_summary(m, resource, connection, jif);
	seq_putc(m, '\n');

	jif = jiffies - jif;
	if (jif)
		seq_printf(m, "generated in %d ms\n", jiffies_to_msecs(jif));
	kref_put(&connection->kref, drbd_destroy_connection);
	return 0;
}