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
struct TYPE_3__ {int stype; int /*<<< orphan*/  sid; int /*<<< orphan*/  stype_env; int /*<<< orphan*/  type; } ;
struct vio_vcc {int /*<<< orphan*/ * data; TYPE_1__ tag; } ;
struct TYPE_4__ {int /*<<< orphan*/  lp; } ;
struct vcc_port {size_t chars_in_buffer; int /*<<< orphan*/  lock; TYPE_2__ vio; struct vio_vcc buffer; } ;
struct tty_struct {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 scalar_t__ VCC_BUFF_LEN ; 
 int VIO_TAG_SIZE ; 
 int /*<<< orphan*/  VIO_TYPE_DATA ; 
 int ldc_write (int /*<<< orphan*/ ,struct vio_vcc*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 struct vcc_port* vcc_get_ne (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcc_kick_tx (struct vcc_port*) ; 
 int /*<<< orphan*/  vcc_put (struct vcc_port*,int) ; 
 int /*<<< orphan*/  vccdbg (char*,int,...) ; 
 int /*<<< orphan*/  vccdbgl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vcc_write(struct tty_struct *tty, const unsigned char *buf,
		     int count)
{
	struct vcc_port *port;
	struct vio_vcc *pkt;
	unsigned long flags;
	int total_sent = 0;
	int tosend = 0;
	int rv = -EINVAL;

	if (unlikely(!tty)) {
		pr_err("VCC: write: Invalid TTY handle\n");
		return -ENXIO;
	}

	port = vcc_get_ne(tty->index);
	if (unlikely(!port)) {
		pr_err("VCC: write: Failed to find VCC port");
		return -ENODEV;
	}

	spin_lock_irqsave(&port->lock, flags);

	pkt = &port->buffer;
	pkt->tag.type = VIO_TYPE_DATA;

	while (count > 0) {
		/* Minimum of data to write and space available */
		tosend = min(count, (VCC_BUFF_LEN - port->chars_in_buffer));

		if (!tosend)
			break;

		memcpy(&pkt->data[port->chars_in_buffer], &buf[total_sent],
		       tosend);
		port->chars_in_buffer += tosend;
		pkt->tag.stype = tosend;

		vccdbg("TAG [%02x:%02x:%04x:%08x]\n", pkt->tag.type,
		       pkt->tag.stype, pkt->tag.stype_env, pkt->tag.sid);
		vccdbg("DATA [%s]\n", pkt->data);
		vccdbgl(port->vio.lp);

		/* Since we know we have enough room in VCC buffer for tosend
		 * we record that it was sent regardless of whether the
		 * hypervisor actually took it because we have it buffered.
		 */
		rv = ldc_write(port->vio.lp, pkt, (VIO_TAG_SIZE + tosend));
		vccdbg("VCC: write: ldc_write(%d)=%d\n",
		       (VIO_TAG_SIZE + tosend), rv);

		total_sent += tosend;
		count -= tosend;
		if (rv < 0) {
			vcc_kick_tx(port);
			break;
		}

		port->chars_in_buffer = 0;
	}

	spin_unlock_irqrestore(&port->lock, flags);

	vcc_put(port, false);

	vccdbg("VCC: write: total=%d rv=%d", total_sent, rv);

	return total_sent ? total_sent : rv;
}