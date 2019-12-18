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
struct xencons_interface {int out_cons; int out_prod; char* out; } ;
struct xencons_info {struct xencons_interface* intf; } ;
typedef  int XENCONS_RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t MASK_XENCONS_IDX (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  notify_daemon (struct xencons_info*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int __write_console(struct xencons_info *xencons,
		const char *data, int len)
{
	XENCONS_RING_IDX cons, prod;
	struct xencons_interface *intf = xencons->intf;
	int sent = 0;

	cons = intf->out_cons;
	prod = intf->out_prod;
	mb();			/* update queue values before going on */
	BUG_ON((prod - cons) > sizeof(intf->out));

	while ((sent < len) && ((prod - cons) < sizeof(intf->out)))
		intf->out[MASK_XENCONS_IDX(prod++, intf->out)] = data[sent++];

	wmb();			/* write ring before updating pointer */
	intf->out_prod = prod;

	if (sent)
		notify_daemon(xencons);
	return sent;
}