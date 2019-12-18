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
typedef  int uint32_t ;
struct hvc_struct {int /*<<< orphan*/  port; } ;
struct hv_ops {int dummy; } ;

/* Variables and functions */
 int MAX_NR_HVC_CONSOLES ; 
 struct hv_ops const** cons_ops ; 
 int /*<<< orphan*/  hvc_check_console (int) ; 
 struct hvc_struct* hvc_get_by_index (int) ; 
 int last_hvc ; 
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 
 int* vtermnos ; 

int hvc_instantiate(uint32_t vtermno, int index, const struct hv_ops *ops)
{
	struct hvc_struct *hp;

	if (index < 0 || index >= MAX_NR_HVC_CONSOLES)
		return -1;

	if (vtermnos[index] != -1)
		return -1;

	/* make sure no no tty has been registered in this index */
	hp = hvc_get_by_index(index);
	if (hp) {
		tty_port_put(&hp->port);
		return -1;
	}

	vtermnos[index] = vtermno;
	cons_ops[index] = ops;

	/* reserve all indices up to and including this index */
	if (last_hvc < index)
		last_hvc = index;

	/* check if we need to re-register the kernel console */
	hvc_check_console(index);

	return 0;
}