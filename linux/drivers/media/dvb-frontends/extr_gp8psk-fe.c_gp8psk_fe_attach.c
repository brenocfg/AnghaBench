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
struct dvb_frontend {struct gp8psk_fe_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct gp8psk_fe_state {int is_rev1; struct dvb_frontend fe; void* priv; struct gp8psk_fe_ops const* ops; } ;
struct gp8psk_fe_ops {int /*<<< orphan*/  reload; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gp8psk_fe_ops ; 
 struct gp8psk_fe_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 

struct dvb_frontend *gp8psk_fe_attach(const struct gp8psk_fe_ops *ops,
				      void *priv, bool is_rev1)
{
	struct gp8psk_fe_state *st;

	if (!ops || !ops->in || !ops->out || !ops->reload) {
		pr_err("Error! gp8psk-fe ops not defined.\n");
		return NULL;
	}

	st = kzalloc(sizeof(struct gp8psk_fe_state), GFP_KERNEL);
	if (!st)
		return NULL;

	memcpy(&st->fe.ops, &gp8psk_fe_ops, sizeof(struct dvb_frontend_ops));
	st->fe.demodulator_priv = st;
	st->ops = ops;
	st->priv = priv;
	st->is_rev1 = is_rev1;

	pr_info("Frontend %sattached\n", is_rev1 ? "revision 1 " : "");

	return &st->fe;
}